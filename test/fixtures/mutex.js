const Thread = require('bare-thread')
const { Mutex } = require('../..')

const mutex = Mutex.from(Thread.self.data)

mutex.lock()
mutex.unlock()
