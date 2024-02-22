window.onload = main

function main() {
    const imageElement = document.body.getElementsByClassName('image')[0]

    if (!imageElement) {
        throw new Error('image not found')
    }

    makeElementDraggable(imageElement)
}

function makeElementDraggable(element) {
    let startPoint = {
        x: 0,
        y: 0
    }

    const onMouseDown = e => {
        startPoint = {
            x: e.clientX - element.offsetLeft,
            y: e.clientY - element.offsetTop,
        }

        window.addEventListener('mousemove', onMouseMove)
        window.addEventListener('mouseup', onMouseUp)
    }

    const onMouseMove = e => {
        const left = px(e.clientX - startPoint.x)
        const top = px(e.clientY - startPoint.y)

        element.setAttribute(
            'style',
            `left: ${left}; top: ${top};`
        )
    }

    const onMouseUp = () => {
        window.removeEventListener('mousemove', onMouseMove)
        window.removeEventListener('mouseup', onMouseUp)
    }

    element.addEventListener('mousedown', onMouseDown)
}

function px(count) {
    return `${count}px`
}