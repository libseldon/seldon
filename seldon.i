%module seldon
%{
#include "SeldonHeader.hxx"
%}

%include "std_string.i"

using namespace std;

// Include the header file with above prototypes
%include "SeldonHeader.hxx"
%include "Common/Common.hxx"
%include "Common/Storage.hxx"
%include "Vector/Vector.hxx"
%include "Common/Allocator.hxx"

namespace Seldon
{
%extend Vector<double, Vect_Full, MallocAlloc<double> >
{
    double __getitem__(int index) {
        if (index < self->GetM())
          return self->GetData()[index];
        else
          return 0;
    }
    void __setitem__(int index, double value) {
        if (index >= 0 && index < self->GetM()) {
            self->GetData()[index] = value;
        }
    }
    unsigned long __len__() {
          return self->GetM();
    }
}
%template(DoubleMalloc) MallocAlloc<double>;
%template(BaseSeldonVector) Vector_Base<double, MallocAlloc<double> >;
%template(VectorDouble) Vector<double, Vect_Full, MallocAlloc<double> >;
}