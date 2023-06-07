const Thread = require('thread')
const test = require('brittle')
const { Semaphore } = require('..')

test('semaphore', (t) => {
  const semaphore = new Semaphore(1)

  semaphore.wait()

  t.comment('lock held')

  const thread = new Thread(__filename, { data: semaphore.handle }, (handle) => {
    const { Semaphore } = require('..')

    Semaphore.from(handle).post()
  })

  semaphore.wait()

  t.comment('lock opened')

  thread.join()

  semaphore.destroy()
})
