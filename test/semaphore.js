const test = require('brittle')
const { Semaphore } = require('..')
const Thread = require('bare-thread')

test('semaphore', (t) => {
  const semaphore = new Semaphore(1)
  t.teardown(() => semaphore.destroy())

  semaphore.wait()

  const thread = new Thread(require.resolve('./fixtures/semaphore'), { data: semaphore.handle })

  semaphore.wait()

  thread.join()

  t.pass()
})
