#ifndef MyEvent_H
#define MyEvent_H

namespace Ko{

  class Event{
    public:

      Event(){}
      virtual ~Event(){}
      Event(unsigned int run, unsigned int lumi, unsigned int event){
        event_ = event;
        run_ = run;
        lumi_ = lumi;
      }

      unsigned int event() const { return event_;}
      unsigned int run() const { return run_;}
      unsigned int lumi() const { return lumi_;}

    private:
      unsigned int event_;
      unsigned int run_;
      unsigned int lumi_;
  };
}
#endif
