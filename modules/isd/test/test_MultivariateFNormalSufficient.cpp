//testing of the Multivariate FNormal. tests return true when they succeed.
#include <IMP/isd/MultivariateFNormalSufficient.h>
#include <IMP/isd/FNormal.h>
#include <IMP/macros.h>
#include <IMP/Pointer.h>
#include <math.h>
#include <IMP/algebra/Vector3D.h>
#include <IMP/algebra/internal/tnt_array2d.h>
#include <IMP/algebra/internal/tnt_array2d_utils.h>
#include <IMP/algebra/internal/jama_lu.h>
#include <IMP/random.h>
#include <boost/random/uniform_real.hpp>

using namespace IMP::isd;

using IMP::algebra::internal::TNT::Array1D;
using IMP::algebra::internal::TNT::Array2D;
using IMP::algebra::internal::JAMA::LU;

//boost::random::mt19937 rnsg;
boost::uniform_real<> uniform(0,1);
//boost::random::variate_generator<boost::mt19937&, boost::uniform_real<> > rand(rnsg,uniform);

#define rand() uniform(IMP::random_number_generator)

#define FAIL(str) {std::cout << str << std::endl; return false;}

#define PRINT(str) std::cout << str << std::endl;

#define RUNTEST(name,nreps) \
for (int i=0; i<nreps; i++){\
    if (!name()){\
        std::cerr << " failed" << std::endl;\
        return 1;\
    }\
}\
std::cerr << " passed" << std::endl;

#define RUNTEST_N(name,nreps,N) \
for (int i=0; i<nreps; i++){\
    if (!name(N)){\
        std::cerr << " failed" << std::endl;\
        return 1;\
    }\
}\
std::cerr << " passed" << std::endl;

//not are equal, in tolerance.
bool naeq(double a, double b, double delta=1e-7){
    if (fabs(b)<=delta){
        if (fabs(a-b) > delta) { 
            std::cout << a << " != " << b << " crit a-b: " << fabs(a-b) << " < " << delta << std::endl;
            return true;
        }
    } else {
        if (a*b <0 || fabs(fabs((double)a/b)-1) > delta) {
            std::cout << a << " != " << b << " crit a/b: " << fabs(fabs(a/b)-1) << " < " << delta << std::endl;
            return true;
        }
    }
    return false;
}

//test when M=100 and N=10
bool test_sanity(){
    //observation matrix
    int M=1+floor(rand()*100);
    int N=1+floor(rand()*100);
    Array2D<double> FA(N,M);
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            FA[i][j] = (rand()*100-50);
        }
    }
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(M);
    for (int i=0; i<M; i++){
        FM[i]=rand()-50;
    }
    //Precision matrix
    Array2D<double> Sigma(M,M,0.0);
    for (int i=0; i<M; i++){
            Sigma[i][i]=1+rand()*10;
    }
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,Sigma));
    //mv->set_was_used(true);

    {
    //evaluate
    double observed=exp(-mv->evaluate());
    double expected=mv->density();
    if (naeq(observed,expected)) FAIL("density->evaluate");
    }

    {
    //density
    double observed=-log(mv->density());
    double expected=mv->evaluate();
    if (! (std::numeric_limits<double>::infinity() == observed)){
        if (naeq(observed,expected)) FAIL("evaluate->density");
    }
    }
    return true;
}

//test when M=1 and N>=1
bool test_1D(int N){
    //observation matrix: N values between 0 and 10
    Array2D<double> FA(N,1);
    for (int i=0; i<N; i++){
        FA[i][0]=rand()*10;
    }
    //Jacobian: normal distribution.
    double JA =1.0;
    //mean vector
    Array1D<double> FM(1,rand()*10);
    //Covariance matrix
    Array2D<double> Sigma(1,1,rand()*10);

    IMP_NEW(IMP::isd::FNormal, fn, (FA[0][0],JA,FM[0],sqrt(Sigma[0][0])));
    //fn->set_was_used(true);
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,Sigma));
    //mv->set_was_used(true);

    //compute sufficient statistics
    double sample_mean = 0;
    for (int i=0; i<N; i++){
        sample_mean += FA[i][0]/double(N);
    }
    double sum_squares = 0;
    for (int i=0; i<N; i++){
        sum_squares += IMP::square(FA[i][0] - sample_mean);
    }

    {
    //test evaluate()
    double observed=mv->evaluate();
    double sigma=sqrt(Sigma[0][0]);
    double expected=(double)N*log((sqrt(2*IMP::PI)*sigma)) + 
        1/(2*sigma*sigma) * ((double)N*IMP::square(sample_mean - FM[0]) + sum_squares);
    //PRINT("evaluate " << observed << " " << expected );
    //if (naeq(observed,expected)) FAIL("evaluate");
    }

    {
    //test density()
    double observed = mv->density();
    double expected=pow(2*IMP::PI*Sigma[0][0],N/2.0) * exp(
            -0.5/Sigma[0][0]*( (double)N*IMP::square(sample_mean - FM[0]) + sum_squares ));
    //PRINT("density " << observed << " " << expected );
    //if (naeq(observed,expected)) FAIL("density");
    }

    {
    //test evaluate_derivative_FM()
    Array1D<double> observed = mv->evaluate_derivative_FM();
    double expected = -double(N)/Sigma[0][0]*(sample_mean - FM[0]);
    //PRINT("FM " << observed[0] << " " << expected );
    if (naeq(observed[0],expected)) FAIL("evaluate_derivative_FM");
    }

    {
    //test evaluate_derivative_Sigma()
    Array2D<double> observed = mv->evaluate_derivative_Sigma();
    double expected = (double)N/(2.0*Sigma[0][0]) 
        - 0.5 / IMP::square(Sigma[0][0]) 
            * ((double)N*IMP::square(sample_mean - FM[0]) + sum_squares);
    PRINT("Sigma " << observed[0][0] << " " << expected << " " << fn->evaluate_derivative_sigma()/(2*sqrt(Sigma[0][0])));
    //if (naeq(observed[0][0],expected)) FAIL("evaluate_derivative_Sigma");
    }
    
    //all tests succeeded.
    return true;
}

//the distribution should coincide with the normal distribution
//when N=M=1
bool test_degenerate(){
    //observation matrix
    Array2D<double> FA(1,1,rand()*10);
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(1,rand()*10);
    //Precision matrix
    Array2D<double> Sigma(1,1,1.0+rand());
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,Sigma));
    //mv->set_was_used(true);
    IMP_NEW(IMP::isd::FNormal, fn, (FA[0][0],JA,FM[0],sqrt(Sigma[0][0])));
    //fn->set_was_used(true);

    {
    //evaluate
    double observed=mv->evaluate();
    double expected=fn->evaluate();
    if (naeq(observed,expected)) FAIL("evaluate");
    }

    {
    //density
    double observed=mv->density();
    double expected=fn->density();
    if (naeq(observed,expected)) FAIL("evaluate");
    }

    {
    //evaluate_derivative_FM
    double observed=mv->evaluate_derivative_FM()[0];
    double expected=fn->evaluate_derivative_FM();
    if (naeq(observed,expected)) FAIL("evaluate_derivative_FM");
    }

    {
    //evaluate_derivative_Sigma
    double observed=mv->evaluate_derivative_Sigma()[0][0];
    double expected=fn->evaluate_derivative_sigma();
    expected=expected/(2*sqrt(Sigma[0][0]));
    if (naeq(observed,expected)) FAIL("evaluate_derivative_Sigma");
    }

    return true;
}

//test when M=2 and N=1
bool test_2D(){
    //observation matrix
    Array2D<double> FA(1,2);
    FA[0][0]=0.5;
    FA[0][1]=1.0;
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(2);
    FM[0]=0.0;
    FM[1]=2.0;
    //Precision matrix
    Array2D<double> Sigma(2,2);
    double sigma1=2.0;
    double sigma2=1.0;
    double rho=0.5;
    Sigma[0][0]=sigma1*sigma1;
    Sigma[1][1]=sigma2*sigma2;
    Sigma[0][1]=rho*sigma1*sigma2;
    Sigma[1][0]=rho*sigma1*sigma2;
    //double factor=1/(rho*rho-1);
    //P[0][0]=-factor/(sigma1*sigma1);
    //P[1][1]=-factor/(sigma2*sigma2);
    //P[0][1]=factor*rho/(sigma1*sigma2);
    //P[1][0]=factor*rho/(sigma1*sigma2);
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,Sigma));
    //mv->set_was_used(true);
    
    {
    //evaluate
    double observed=mv->evaluate();
    double expected=log(2*IMP::PI*sigma1*sigma2*sqrt(1-rho*rho)) + 
        1/(2*(1-rho*rho)) * ( IMP::square(FA[0][0] - FM[0])/(sigma1*sigma1) + IMP::square(FA[0][1]-FM[1])/(sigma2*sigma2)
                - 2*rho*(FA[0][0]-FM[0])*(FA[0][1]-FM[1])/(sigma1*sigma2));
    if (naeq(observed,expected)) FAIL("evaluate");
    }

    {
    //density
    double observed=mv->density();
    double expected=1/(2*IMP::PI*sigma1*sigma2*sqrt(1-rho*rho))*exp(
        -1/(2*(1-rho*rho)) * ( IMP::square(FA[0][0] - FM[0])/(sigma1*sigma1) + IMP::square(FA[0][1]-FM[1])/(sigma2*sigma2)
                - 2*rho*(FA[0][0]-FM[0])*(FA[0][1]-FM[1])/(sigma1*sigma2)));
    if (naeq(observed,expected)) FAIL("density");
    }

    {
    //test_evaluate_derivative_FM
    Array1D<double> observed=mv->evaluate_derivative_FM();
    double expected=((FM[1]-FA[0][1])*rho*sigma1 + (FA[0][0]-FM[0])*sigma2)/((-1+rho*rho)*sigma1*sigma1*sigma2);
    if (naeq(observed[0],expected)) FAIL("derivative_FM[0]");
    expected=((FA[0][1]-FM[1])*sigma1 + (FM[0]-FA[0][0])*rho*sigma2)/((-1+rho*rho)*sigma1*sigma2*sigma2);
    if (naeq(observed[1],expected)) FAIL("derivative_FM[1]");
    }

    {
    //test_evaluate_derivative_Sigma
    double det=Sigma[0][0]*Sigma[1][1]-Sigma[0][1]*Sigma[1][0];
    double eps1=FA[0][0]-FM[0];
    double eps2=FA[0][1]-FM[1];
    Array2D<double> observed=mv->evaluate_derivative_Sigma();
    double expected=0.5/IMP::square(det) 
        * (   IMP::square(Sigma[1][1]) * (Sigma[0][0] - eps1) 
            - IMP::square(Sigma[0][1]) * (Sigma[1][1] + eps2)
            + 2*Sigma[0][1]*Sigma[1][1]*eps1*eps2 );
    if (naeq(observed[0][0],expected)) FAIL("derivative_P[0][0]");
    expected=0.5/IMP::square(det)
        * (   IMP::square(Sigma[0][0]) * (Sigma[1][1] - eps2) 
            + 2*Sigma[1][0]*Sigma[0][0]*eps2*eps1 );
    if (naeq(observed[1][1],expected)) FAIL("derivative_P[1][1]");
    expected=1.0/IMP::square(det)
        * ( Sigma[0][1]*(det+Sigma[1][1]*IMP::square(eps1)+Sigma[0][0]*IMP::square(eps2))
            - eps1*eps2*(IMP::square(Sigma[1][0])+Sigma[0][0]*Sigma[1][1]) );
    if (naeq(observed[0][1],expected)) FAIL("derivative_P[0][1]");
    if (naeq(observed[1][0],expected)) FAIL("derivative_P[1][0]");
    }
    return true;
}

//test when M=100 and N=10
bool test_100D(){
    //observation matrix
    Array2D<double> FA(10,100);
    for (int i=0; i<10; i++){
        for (int j=0; j<100; j++){
            // a little bit beneath the maximum.
            FA[i][j] = double( i-2 + j-54 ); 
        }
    }
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(100);
    for (int i=0; i<100; i++){
        FM[i]=i-49.0;
    }
    //Covariance matrix
    Array2D<double> Sigma(100,100,0.0);
    for (int i=0; i<100; i++){
            Sigma[i][i]=1.0;
    }
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,Sigma));
    //mv->set_was_used(true);

    {
    //evaluate
    double observed=mv->evaluate();
    double expected=8168.938533204672717;
    if (naeq(observed,expected)) FAIL("evaluate");
    }

    return true;
}

/*
//test when M=2 and N=1 TODO: P->Sigma
bool gen_2D(){
    //observation matrix
    Array2D<double> FA(1,2);
    FA[0][0]=0.5;
    FA[0][1]=1.0;
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(2);
    FM[0]=0.0;
    FM[1]=2.0;
    //Precision matrix
    Array2D<double> P(2,2);
    double sigma1=2.0;
    double sigma2=1.0;
    double rho=0.5;
    //P[0][0]=sigma1*sigma1;
    //P[1][1]=sigma2*sigma2;
    //P[0][1]=rho*sigma1*sigma2;
    //P[1][0]=rho*sigma1*sigma2;
    double factor=1/(rho*rho-1);
    P[0][0]=-factor/(sigma1*sigma1);
    P[1][1]=-factor/(sigma2*sigma2);
    P[0][1]=factor*rho/(sigma1*sigma2);
    P[1][0]=factor*rho/(sigma1*sigma2);

    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,P));
    //mv->set_was_used(true);
    
    for (int i=0; i<1000; i++){
    double mu1=((double)i - 500)/100.0;
    FM[0]=mu1;
    mv->set_FM(FM);
    //evaluate
    Array1D<double> observed=mv->evaluate_derivative_FM();
    double expected=((FM[1]-FA[0][1])*rho*sigma1 + (FA[0][0]-FM[0])*sigma2)/((-1+rho*rho)*sigma1*sigma1*sigma2);
    double expected2=((FA[0][1]-FM[1])*sigma1 + (FM[0]-FA[0][0])*rho*sigma2)/((-1+rho*rho)*sigma1*sigma2*sigma2);
    PRINT(mu1 << " " << observed[0] << " " << expected << " " << observed[1] << " " << expected2);
    }
    return true;
}

//test with N MultivariateFNormalSufficient instances TODO
bool test_degenerate_2(int N){
    //observation matrix
    Array2D<double> FA(N,1);
    for (int i=0; i<N; i++){
        FA[i][0]=rand()*10;
    }
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(1,rand()*10);
    //Precision matrix
    Array2D<double> P(1,1,1.0+rand());
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,P));
    //mv->set_was_used(true);
    IMP::Pointer<IMP::isd::MultivariateFNormalSufficient> * fn;
    fn = new IMP::Pointer<IMP::isd::MultivariateFNormalSufficient> [N];
    for (int i=0; i< N; i++){
        Array2D<double> a(1,1,FA[i][0]);
        Array1D<double> m(1,FM[i]);
        fn[i] = new IMP::isd::MultivariateFNormalSufficient(a,JA,m,P);
        //fn[i]->set_was_used(true);
    }

    {
    //evaluate
    double observed=mv->evaluate();
    double expected=0.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate();
    }
    if (naeq(observed,expected)) FAIL("evaluate");
    }

    {
    //density
    double observed=mv->density();
    double expected=1.0;
    for (int i=0; i<N; i++){
        expected *= fn[i]->density();
    }
    if (naeq(observed,expected)) FAIL("density");
    }

    {
    //evaluate_derivative_FM
    double observed=mv->evaluate_derivative_FM()[0];
    double expected=0.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate_derivative_FM()[0];
    }
    if (naeq(observed,expected)) FAIL("evaluate_derivative_FM");
    }

    {
    //evaluate_derivative_P
    double observed=mv->evaluate_derivative_P()[0][0];
    double expected=0.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate_derivative_P()[0][0];
    }
    if (naeq(observed,expected)) FAIL("evaluate_derivative_P");
    }

    return true;
}

//test with M=1 and N=2, varying mu TODO
bool test_mu(int N){
    //observation matrix
    Array2D<double> FA(N,1,0.0);
    //for (int i=0; i<N; i++){
    //    FA[i][0]=rand()*10;
    //}
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(1,0.0);
    //Precision matrix
    Array2D<double> P(1,1,1.1);
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,P));
    //mv->set_was_used(true);
    IMP::Pointer<IMP::isd::MultivariateFNormalSufficient> * fn;
    IMP::Pointer<IMP::isd::FNormal> * fn2;
    fn = new IMP::Pointer<IMP::isd::MultivariateFNormalSufficient> [N];
    fn2 = new IMP::Pointer<IMP::isd::FNormal> [N];
    for (int i=0; i< N; i++){
        Array2D<double> a(1,1,FA[i][0]);
        Array1D<double> m(1,FM[i]);
        fn[i] = new IMP::isd::MultivariateFNormalSufficient(a,JA,m,P);
        //fn[i]->set_was_used(true);
        fn2[i] = new IMP::isd::FNormal(a[0][0],JA,m[0],1/sqrt(P[0][0]));
        //fn2[i]->set_was_used(true);
    }

    for (int k=0; k<1000; k++) {
    double mu=((double)k-500.0)/10.0;
    FM[0]=mu;
    mv->set_FM(FM);
    //evaluate
    double observed=mv->evaluate();
    double dobs=mv->density();
    double expected=0.0;
    double expected2=0.0;
    double dexp=1.0;
    double dexp2=1.0;
    for (int i=0; i<N; i++){
        fn[i]->set_FM(FM);
        fn2[i]->set_FM(mu);
        expected += fn[i]->evaluate();
        expected2 += fn2[i]->evaluate();
        dexp *= fn[i]->density();
        dexp2 *= fn2[i]->density();
    }
    PRINT(mu << " " << observed << " " << expected << " " << expected2 << " " << dobs << " " << dexp << " " << dexp2);
    }

    return true;
}

//test with N FNormal instances
//test with N MultivariateFNormalSufficient instances TODO
bool test_test(int N){
    //observation matrix
    Array2D<double> FA(N,1,0.0);
    //for (int i=0; i<N; i++){
    //    FA[i][0]=rand()*10;
    //}
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(1,0.0);
    //Precision matrix
    Array2D<double> P(1,1,1.1);
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,P));
    //mv->set_was_used(true);
    IMP::Pointer<IMP::isd::MultivariateFNormalSufficient> * fn;
    IMP::Pointer<IMP::isd::FNormal> * fn2;
    fn = new IMP::Pointer<IMP::isd::MultivariateFNormalSufficient> [N];
    fn2 = new IMP::Pointer<IMP::isd::FNormal> [N];
    for (int i=0; i< N; i++){
        Array2D<double> a(1,1,FA[i][0]);
        Array1D<double> m(1,FM[i]);
        fn[i] = new IMP::isd::MultivariateFNormalSufficient(a,JA,m,P);
        //fn[i]->set_was_used(true);
        fn2[i] = new IMP::isd::FNormal(a[0][0],JA,m[0],1/sqrt(P[0][0]));
        //fn2[i]->set_was_used(true);
    }

    {
    //evaluate
    double observed=mv->evaluate();
    double dobs=mv->density();
    double expected=0.0;
    double expected2=0.0;
    double dexp=1.0;
    double dexp2=1.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate();
        expected2 += fn2[i]->evaluate();
        dexp *= fn[i]->density();
        dexp2 *= fn2[i]->density();
    }
    PRINT(N << " "<< observed << " " << expected << " " << expected2 << " " << dobs << " " << dexp << " " << dexp2);
    }

    return true;
}

//test with N FNormal instances TODO
bool test_degenerate_N(int N){
    //observation matrix
    Array2D<double> FA(N,1);
    for (int i=0; i<N; i++){
        FA[i][0]=rand()*10;
    }
    //Jacobian
    double JA =1.0;
    //mean vector
    Array1D<double> FM(1,rand()*10);
    //Precision matrix
    Array2D<double> P(1,1,1.0+rand());
    
    IMP_NEW(IMP::isd::MultivariateFNormalSufficient, mv, (FA,JA,FM,P));
    //mv->set_was_used(true);
    IMP::Pointer<IMP::isd::FNormal> * fn;
    fn = new IMP::Pointer<IMP::isd::FNormal> [N];
    for (int i=0; i< N; i++){
        fn[i] = new IMP::isd::FNormal(FA[i][0],JA,FM[i],sqrt(1.0/P[0][0]));
        //fn[i]->set_was_used(true);
    }

    {
    //evaluate
    double observed=mv->evaluate();
    double expected=0.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate();
    }
    if (naeq(observed,expected)) FAIL("evaluate");
    }

    {
    //density
    double observed=mv->density();
    double expected=1.0;
    for (int i=0; i<N; i++){
        expected *= fn[i]->density();
    }
    if (naeq(observed,expected)) FAIL("density");
    }

    {
    //evaluate_derivative_FM
    double observed=mv->evaluate_derivative_FM()[0];
    double expected=0.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate_derivative_FM();
    }
    if (naeq(observed,expected)) FAIL("evaluate_derivative_FM");
    }

    {
    //evaluate_derivative_P
    double observed=mv->evaluate_derivative_P()[0][0];
    double expected=0.0;
    for (int i=0; i<N; i++){
        expected += fn[i]->evaluate_derivative_sigma()/(-2.0*pow(P[0][0],1.5));
    }
    if (naeq(observed,expected)) FAIL("evaluate_derivative_P");
    }

    return true;
}
*/

int main(int, char *[]) {
    try {
    //test_mu(20);
    //return 0;
    //for (int i=1; i<100; i++){
    //    test_test(i);
    //}
    //return 0;
    //gen_2D();
    //return 0;
    PRINT("sanity");
    RUNTEST(test_sanity,100);
    PRINT("1D 1");
    RUNTEST_N(test_1D,100,1);
    PRINT("1D 2");
    RUNTEST_N(test_1D,100,2);
    PRINT("1D 10");
    RUNTEST_N(test_1D,100,10);
    PRINT("1D 100");
    RUNTEST_N(test_1D,100,100);
    PRINT("degenerate");
    RUNTEST(test_degenerate,100);
    //PRINT("degenerate N=2");
    //RUNTEST_N(test_degenerate_2,100,2);
    //return 0;
    //PRINT("degenerate N=10");
    //RUNTEST_N(test_degenerate_N,100,10);
    //PRINT("degenerate N=100");
    //RUNTEST_N(test_degenerate_N,100,100);
    PRINT("2D");
    RUNTEST(test_2D,100);
    PRINT("100D");
    RUNTEST(test_100D,1);
    //TODO
    //PRINT("setting values");
    //RUNTEST(test_setval,1);
    return 0;
    } catch (const IMP::ExceptionBase& e) {
        std::cerr << e.what() << std::endl;
    }
}



