window.onload = start

function start() {
    const PANIC = (msg) => {
        throw new Error(msg)
    }

    const px = count => `${count}px`

    const imageElement = document.body.getElementsByClassName('image')[0]

    if (!imageElement) {
        PANIC('image not found')
    }

    let delta = {
        x: 0,
        y: 0
    }

    const onMouseDown = e => {
        window.addEventListener('mousemove', onMouseMove)
        window.addEventListener('mouseup', onMouseUp)
        delta = {
            x: e.clientX - imageElement.offsetLeft,
            y: e.clientY - imageElement.offsetTop,
        }
    }

    const onMouseMove = e => {
        imageElement.setAttribute('style', `left: ${px(e.clientX - delta.x)}; top: ${px(e.clientY - delta.y)}`)
    }

    const onMouseUp = e => {
        window.removeEventListener('mousemove', onMouseMove)
        window.removeEventListener('mouseup', onMouseUp)
    }

    imageElement.addEventListener('mousedown', onMouseDown)
}
