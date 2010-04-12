/**
 *  \file Decorators.h    \brief The base class for decorators.
 *
 *  Copyright 2007-2010 IMP Inventors. All rights reserved.
 *
 */

#ifndef IMP_DECORATORS_H
#define IMP_DECORATORS_H

#include "Decorator.h"
#include "internal/IndexingIterator.h"

IMP_BEGIN_NAMESPACE


#if !defined(SWIG)
#define IMP_DECORATORS_METHODS(test, on_add_decorator, on_add_particle, \
                               swap)                                    \
  struct Accessor {                                                     \
  typedef Accessor This;                                                \
  typedef WrappedDecorator result_type;                                 \
  typedef unsigned int argument_type;                                   \
  result_type operator()(argument_type i) const {                       \
    return o_->operator[](i);                                           \
  }                                                                     \
  Accessor(ThisDecorators *pc): o_(pc){}                                \
  Accessor(): o_(NULL){}                                                \
  IMP_COMPARISONS_1(o_);                                                \
private:                                                                \
/* This should be ref counted, but swig memory management
   is broken */                                                         \
ThisDecorators* o_;                                                     \
};                                                                      \
void check(Particle *p) {                                               \
  IMP_USAGE_CHECK(test,                                                 \
                  "Particle \"" << (p)->get_name()                      \
                  << "\" missing required attributes");                 \
}                                                                       \
template <class It>                                                     \
void check(It b, It e) {                                                \
  for (It c= b; c!= e; ++c) {                                           \
    check(*c);                                                          \
  }                                                                     \
}                                                                       \
public:                                                                 \
typedef const WrappedDecorator const_reference;                         \
typedef WrappedDecorator value_type;                                    \
typedef Proxy reference;                                                \
const ParticlesTemp &get_particles() const {return *this;}              \
void push_back(WrappedDecorator d) {                                    \
  on_add_decorator;                                                     \
  typename ParentDecorators::value_type pd=d;                           \
  ParentDecorators::push_back(pd);                                      \
}                                                                       \
void push_back(Particle *p) {                                           \
  check(p);                                                             \
  on_add_particle;                                                      \
  typename ParentDecorators::value_type pd=WrappedDecorator(p);         \
  ParentDecorators::push_back(pd);                                      \
}                                                                       \
void set(unsigned int i, WrappedDecorator d) {                          \
  typename ParentDecorators::value_type pd=d;                           \
  ParentDecorators::operator[](i)= pd;                                  \
}                                                                       \
WrappedDecorator back() const {                                         \
  IMP_USAGE_CHECK(!ParentDecorators::empty(),                           \
                  "Can't call back on empty Decorators");               \
  return WrappedDecorator(ParentDecorators::back());                    \
}                                                                       \
WrappedDecorator front() const {                                        \
  IMP_USAGE_CHECK(!ParentDecorators::empty(),                           \
                  "Can't call front on empty Decorators");              \
  return WrappedDecorator(ParentDecorators::front());                   \
}                                                                       \
typedef internal::IndexingIterator<Accessor> iterator;                  \
typedef internal::IndexingIterator<Accessor> const_iterator;            \
iterator begin() const {                                                \
  return iterator(Accessor(const_cast<ThisDecorators*>(this)), 0);      \
}                                                                       \
iterator end() const {                                                  \
  return iterator(Accessor(const_cast<ThisDecorators*>(this)),          \
                  ParentDecorators::size());                            \
}                                                                       \
template <class It>                                                     \
void insert(iterator loc, It b, It e) {                                 \
  check(b,e);                                                           \
  for (It c=b; c!= e; ++c) {                                            \
    on_add_particle;                                                    \
  }                                                                     \
  ParentDecorators::insert(ParentDecorators::begin()+(loc-begin()),     \
                           b, e);                                       \
}                                                                       \
void swap_with(ThisDecorators &o) {                                     \
  swap;                                                                 \
  ParentDecorators::swap_with(o);                                       \
}                                                                       \

#else
#define IMP_DECORATORS_METHODS(test, on_add_decorator, on_add_particle, \
                               swap)                                    \
  public:                                                               \
  const ParticlesTemp &get_particles() const;                           \
  void push_back(WrappedDecorator d);                                   \
  void push_back(Particle *p);                                          \
  WrappedDecorator back() const;                                        \
  WrappedDecorator front() const;

#endif


template <class WrappedDecorator, class ParentDecorators, class Enabled=void>
class Decorators: public ParentDecorators {
  typedef Decorators<WrappedDecorator, ParentDecorators> ThisDecorators;
  struct Proxy: public WrappedDecorator {
    typedef typename ParentDecorators::reference Ref;
    Ref d_;
    Proxy(Ref t):
      WrappedDecorator(t), d_(t){
    }
    Proxy(Ref p, bool): WrappedDecorator(), d_(p){}
    void operator=(WrappedDecorator v) {
      WrappedDecorator::operator=(v);
      d_=v;
    }
#if 0
    // for VC, it can't otherwise figure out the conversion chain
    operator Particle*() {
      if (WrappedDecorator()==*this) return NULL;
      else return WrappedDecorator::get_particle();
    }
#endif
  };
  Proxy get_proxy(unsigned int i) {
    if (ParentDecorators::operator[](i)) {
      return Proxy(ParentDecorators::operator[](i));
    } else {
      return Proxy(ParentDecorators::operator[](i), false);
    }
  }

  IMP_DECORATORS_METHODS(WrappedDecorator::particle_is_instance(p),{},{},{});
  public:
  explicit Decorators(const Particles &ps) {
    check(ps.begin(), ps.end());
    ParentDecorators::reserve(ps.size());
    for (unsigned int i=0; i< ps.size(); ++i) {
      push_back(ps[i]);
    }
  }
  explicit Decorators(const ParticlesTemp &ds) {
    check(ds.begin(), ds.end());
    ParentDecorators::reserve(ds.size());
    for (unsigned int i=0; i< ds.size(); ++i) {
      push_back(ds[i]);
    }
  }
  explicit Decorators(unsigned int i): ParentDecorators(i, WrappedDecorator()){}
  explicit Decorators(WrappedDecorator d): ParentDecorators(1, d){}
  explicit Decorators(unsigned int n,
                      WrappedDecorator d): ParentDecorators(n, d){}
  template <class It>
  Decorators(It b, It e): ParentDecorators(b,e){check(b,e);}
  Decorators(){}
#ifndef SWIG
  Proxy
  operator[](unsigned int i) {
    return get_proxy(i);
  }
#endif

#ifndef SWIG
  WrappedDecorator operator[](unsigned int i) const {
    return WrappedDecorator(ParentDecorators::operator[](i));
  }
#endif
};

template <class WrappedDecorator, class ParentDecorators>
class Decorators<WrappedDecorator, ParentDecorators,
typename boost::enable_if<typename WrappedDecorator::DecoratorHasTraits>::type >
  : public ParentDecorators {
  typedef Decorators<WrappedDecorator, ParentDecorators> ThisDecorators;

  struct Proxy: public WrappedDecorator {
    typedef typename ParentDecorators::reference Ref;
    Ref d_;
    typename WrappedDecorator::DecoratorTraits &tr_;
    bool has_traits_;
    Proxy(Ref t, typename WrappedDecorator::DecoratorTraits &tr,
          bool ht):
      WrappedDecorator(t, tr), d_(t), tr_(tr), has_traits_(ht){
    }
    Proxy(Ref p, typename WrappedDecorator::DecoratorTraits &tr,
          bool ht, bool): WrappedDecorator(), d_(p), tr_(tr),
                          has_traits_(ht){}
    void operator=(WrappedDecorator v) {
      // traits should match, but not checked
      WrappedDecorator::operator=(v);
      if (!has_traits_) {
        tr_= v.get_decorator_traits();
        IMP_USAGE_CHECK(tr_==tr_, "Traits must match themselves");
      } else if (v != WrappedDecorator()) {
        IMP_USAGE_CHECK(tr_== v.get_decorator_traits(),
                        "Traits don't match");
      }
      d_=v;
    }
#if 0
    // for VC, it can't otherwise figure out the conversion chain
    operator Particle*() {
      if (WrappedDecorator()==*this) return NULL;
      else return WrappedDecorator::get_particle();
    }
#endif
  };
  Proxy get_proxy(unsigned int i) {
    if (ParentDecorators::operator[](i)) {
      return Proxy(ParentDecorators::operator[](i), tr_, has_traits_);
    } else {
      return Proxy(ParentDecorators::operator[](i), tr_, has_traits_, false);
    }
  }
  typename WrappedDecorator::DecoratorTraits tr_;
  bool has_traits_;
  IMP_DECORATORS_METHODS(WrappedDecorator::particle_is_instance(p, tr_),{
      if (!has_traits_) {
        tr_= d.get_decorator_traits();
        has_traits_=true;
      } else {
        IMP_USAGE_CHECK(tr_ == d.get_decorator_traits(),
                        "Traits don't match");
      }
    },{
      IMP_USAGE_CHECK(has_traits_, "Need to add a decorator first to get "
                      << "traits class.");
    }, {
      std::swap(tr_, o.tr_);
      std::swap(has_traits_, o.has_traits_);
    });
    static typename WrappedDecorator::DecoratorTraits
    get_default_traits() {
       return WrappedDecorator::get_default_decorator_traits();
    }
  public:
  explicit Decorators(typename WrappedDecorator::DecoratorTraits tr):
    tr_(tr), has_traits_(true){}
  explicit Decorators(WrappedDecorator d): ParentDecorators(1,d){
    if (d) {
      tr_=d.get_decorator_traits();
      has_traits_=true;
    }
  }
  explicit Decorators(unsigned int n, WrappedDecorator d):
    ParentDecorators(n, d)
     {
       if (d) {
         tr_=d.get_decorator_traits();
         has_traits_=true;
       }
     }
  template <class It>
  Decorators(It b, It e): ParentDecorators(b,e), has_traits_(false) {
    check(b,e);
  }
  Decorators(const Particles &ps,
             typename WrappedDecorator::DecoratorTraits tr):
    tr_(tr), has_traits_(true) {
    ParentDecorators::resize(ps.size());
    for (unsigned int i=0; i< ps.size(); ++i) {
      ParentDecorators::operator[](i)=WrappedDecorator(ps[i], tr);
    }
  }
  Decorators(const Particles &ps):
    tr_(get_default_traits()), has_traits_(true) {
      ParentDecorators::resize(ps.size());
      for (unsigned int i=0; i< ps.size(); ++i) {
         ParentDecorators::operator[](i)=WrappedDecorator(ps[i],
              tr_);
      }
    }
  Decorators(unsigned int i,
                       typename WrappedDecorator::DecoratorTraits tr):
    ParentDecorators(i), tr_(tr),
    has_traits_(true){}
  Decorators(unsigned int i):
    ParentDecorators(i),
    has_traits_(false){}
  Decorators(): has_traits_(false){}

#ifndef SWIG
  Proxy
  operator[](unsigned int i) {
    return get_proxy(i);
  }
  WrappedDecorator operator[](unsigned int i) const {
    if (ParentDecorators::operator[](i)) {
      return WrappedDecorator(ParentDecorators::operator[](i), tr_);
    } else {
      return WrappedDecorator();
    }
  }
#endif
};

IMP_SWAP_2(Decorators);



IMP_END_NAMESPACE

#endif  /* IMP_DECORATORS_H */
