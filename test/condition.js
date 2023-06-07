const Thread = require('thread')
const test = require('brittle')
const { Condition, Mutex } = require('..')

test('condition', (t) => {
  const condition = new Condition()
  t.teardown(() => condition.destroy())

  const thread = new Thread(__filename, { data: condition.handle }, (handle) => {
    const { Condition } = require('..')

    Condition.from(handle).signal()
  })

  const mutex = new Mutex()
  t.teardown(() => mutex.destroy())

  mutex.lock()

  condition.wait(mutex)

  mutex.unlock()

  thread.join()

  t.pass()
})
