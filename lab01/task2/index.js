window.onload = start

function start() {
    const px = count => `${count}px`

    const imageElement = document.body.getElementsByClassName('image')[0]

    if (!imageElement) {
        throw new Error('image not found')
    }

    let startPoint = {
        x: 0,
        y: 0
    }

    const onMouseDown = e => {
        startPoint = {
            x: e.clientX - imageElement.offsetLeft,
            y: e.clientY - imageElement.offsetTop,
        }

        window.addEventListener('mousemove', onMouseMove)
        window.addEventListener('mouseup', onMouseUp)
    }

    const onMouseMove = e => {
        const left = px(e.clientX - startPoint.x)
        const top = px(e.clientY - startPoint.y)

        imageElement.setAttribute(
            'style',
            `left: ${left}; top: ${top};`
        )
    }

    const onMouseUp = () => {
        window.removeEventListener('mousemove', onMouseMove)
        window.removeEventListener('mouseup', onMouseUp)
    }

    imageElement.addEventListener('mousedown', onMouseDown)
}
