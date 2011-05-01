// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "thread/Thread.h"

#include <boost/scoped_ptr.hpp>
#include <vector>

namespace muduo
{

class Channel;
class Poller;

class EventLoop : boost::noncopyable
{
 public:

  EventLoop();
  ~EventLoop();

  void loop();
  void quit();

  // internal use only
  void updateChannel(Channel* channel);
  void removeChannel(Channel* channel);

  void assertInLoopThread()
  {
    if (!isInLoopThread())
    {
      abortNotInLoopThread();
    }
  }

  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

 private:

  typedef std::vector<Channel*> ChannelList;

  void abortNotInLoopThread();

  bool looping_; /* atomic */
  bool quit_; /* atomic */
  const pid_t threadId_;
  boost::scoped_ptr<Poller> poller_;
  ChannelList activeChannels_;

};

}

#endif  // MUDUO_NET_EVENTLOOP_H
