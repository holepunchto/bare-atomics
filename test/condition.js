const test = require('brittle')
const { Condition, Mutex } = require('..')
const Thread = require('bare-thread')

test('condition', (t) => {
  const condition = new Condition()
  t.teardown(() => condition.destroy())

  const thread = new Thread(require.resolve('./fixtures/condition'), { data: condition.handle })

  const mutex = new Mutex()
  t.teardown(() => mutex.destroy())

  mutex.lock()

  condition.wait(mutex)

  mutex.unlock()

  thread.join()

  t.pass()
})
