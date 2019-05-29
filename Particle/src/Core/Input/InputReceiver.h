#ifndef INPUTRECEIVER_H
#define INPUTRECEIVER_H

namespace PT
{
    class InputReceiver
    {
    private:
        
    public:
        InputReceiver() {}
        virtual ~InputReceiver() {}
        
        virtual void register_input_dispatch() = 0;
        virtual void receive_dispatched_input(unsigned int key) = 0;
    };
}


#endif /* INPUTRECEIVER_H */
