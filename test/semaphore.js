const Thread = require('thread')
const test = require('brittle')
const { Semaphore } = require('..')

test('semaphore', (t) => {
  const semaphore = new Semaphore(1)
  t.teardown(() => semaphore.destroy())

  semaphore.wait()

  const thread = new Thread(__filename, { data: semaphore.handle }, (handle) => {
    const { Semaphore } = require('..')

    Semaphore.from(handle).post()
  })

  semaphore.wait()

  thread.join()

  t.pass()
})
