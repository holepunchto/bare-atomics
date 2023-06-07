const Thread = require('thread')
const test = require('brittle')
const { Mutex } = require('..')

test('mutex', (t) => {
  const mutex = new Mutex()

  mutex.lock()

  t.comment('lock held')

  const thread = new Thread(__filename, { data: mutex.handle }, (handle) => {
    const { Mutex } = require('..')

    const mutex = Mutex.from(handle)

    mutex.lock()
    mutex.unlock()
  })

  mutex.unlock()

  t.comment('lock opened')

  thread.join()

  mutex.destroy()
})
