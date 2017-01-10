//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_LOOP_H
#define KATRINA_LOOP_H

namespace donet {
    class Loop {
    public:
        virtual ~Loop() {

        }

        void Start() {
            _Run();
        }

    protected:
        virtual void _Run() = 0;
    };
}
#endif //KATRINA_LOOP_H
