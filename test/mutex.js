const Thread = require('thread')
const test = require('brittle')
const { Mutex } = require('..')

test('mutex', (t) => {
  const mutex = new Mutex()
  t.teardown(() => mutex.destroy())

  const thread = new Thread(__filename, { data: mutex.handle }, (handle) => {
    const { Mutex } = require('..')

    const mutex = Mutex.from(handle)

    mutex.lock()
    mutex.unlock()
  })

  mutex.lock()
  mutex.unlock()

  thread.join()

  t.pass()
})
