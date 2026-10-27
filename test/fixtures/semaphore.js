const Thread = require('bare-thread')
const { Semaphore } = require('../..')

Semaphore.from(Thread.self.data).post()
