const Thread = require('bare-thread')
const { Condition } = require('../..')

Condition.from(Thread.self.data).signal()
