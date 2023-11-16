/* global Bare */
const test = require('brittle')
const { Barrier } = require('..')
const { Thread } = Bare

test('barrier', (t) => {
  const barrier = new Barrier(2)

  const thread = new Thread(__filename, { data: barrier.handle }, (handle) => {
    const { Barrier } = require('..')

    const barrier = Barrier.from(handle)

    if (barrier.wait()) barrier.destroy()
  })

  if (barrier.wait()) barrier.destroy()

  thread.join()

  t.pass()
})
