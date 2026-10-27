const test = require('brittle')
const { Mutex } = require('..')
const Thread = require('bare-thread')

test('mutex', (t) => {
  const mutex = new Mutex()
  t.teardown(() => mutex.destroy())

  const thread = new Thread(require.resolve('./fixtures/mutex'), { data: mutex.handle })

  mutex.lock()
  mutex.unlock()

  thread.join()

  t.pass()
})
