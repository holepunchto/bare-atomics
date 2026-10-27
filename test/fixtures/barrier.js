const Thread = require('bare-thread')
const { Barrier } = require('../..')

const barrier = Barrier.from(Thread.self.data)

if (barrier.wait()) barrier.destroy()
