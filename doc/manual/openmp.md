OpenMP {#openmp}
======

%IMP supports multithreaded evaluation using [OpenMP](http://openmp.org/wp/)
(version 3.0 or later). This is automatically supported on Linux, but not
currently on Mac or Windows (the compilers there do not support OpenMP).

Multithreaded evaluation uses OpenMP tasks, with each IMP::kernel::Restraint or IMP::kernel::ScoreState being made into one or more tasks that are executed independently. %IMP uses the information in the IMP::kernel::DepdendencyGraph to automatically determine which IMP::kernel::ScoreState objects can be used in parallel. That is, two score states are independent if neither depend on data written by the other.

## Controlling OpenMP

By default, %IMP runs on a single thread (i.e. not parallel). This can be
changed by calling the IMP::base::set_number_of_threads() function, using
the RAII class IMP::base::SetNumberOfThreads, or setting the command line flag
"number_of_threads" in executables that use %IMP's flags support.
The IMP::base::get_number_of_threads() returns the current number of threads
being used.

## Writing code with OpenMP

If you want to parallelize code, see the helper macros in base/thread_macros.h. In particular, you can define a new task with IMP_TASK() and make your executable multithreaded with IMP_THREADS(). If you define tasks yourself, be sure to add

      #pragma omp taskwait

to make sure all the tasks are finished before returning. In general, you probably need to read various OpenMP documentation to get things to work right. IMP::kernel::Restraints that want to create tasks should implement IMP::kernel::Restraint::do_add_score_and_derivatives() rather than IMP::kernel::Restraint::unprotected_evaluate() as it is hard to properly get the return value back otherwise.

Examples will come.