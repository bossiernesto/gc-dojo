#include <stdexcept>
#include "cspec.h"
#include "markandreallocate.cpp"

/*int main(int argc, char **argv) {

    describe("Test GC", function()
            {

                it("Test add push to stack", function()
                {
                    GCEnviroment *gc = new GCEnviroment(nullptr, 0, 0, 10);
                    gc->pushInt(54);
                    should_int(gc->getStackSize()) be equal to(1);
                });

                it("Push two values and pop one", function(){
                    GCEnviroment *gc = new GCEnviroment(nullptr, 0, 0, 10);
                    gc->pushInt(42);
                    gc->pushInt(12);
                    should_int(gc->getNumObjects()) be equal to(2);
                    should_int(gc->getStackSize()) be equal to(2);
                    gc->pop();
                    should_int(gc->getNumObjects()) be equal to(2);
                    gc->garbageCollect();
                    should_int(gc->getNumObjects()) be equal to(1);
                });

                it("Push three values and pop a tuple", function(){
                    GCEnviroment *gc = new GCEnviroment(nullptr, 0, 0, 10);
                    gc->pushInt(42);
                    gc->pushInt(12);
                    gc->pushInt(23);
                    gc->pushTuple();
                    gc->garbageCollect();
                    should_int(gc->getNumObjects()) be equal to(1);

                });

            });

    return CSPEC_RESULT;
}
*/