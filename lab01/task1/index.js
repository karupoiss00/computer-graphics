window.onload = main

function main() {
    const firstLetter = document.body.getElementsByClassName('g-letter')[0]
    const secondLetter = document.body.getElementsByClassName('r-letter')[0]
    const thirdLetter = document.body.getElementsByClassName('m-letter')[0]

    if (!firstLetter || !secondLetter || !thirdLetter) {
        throw new Error('one of letter elements is undefined')
    }

    const {animate: animateFirst} = createDropAnimation(firstLetter, 2000, 100)
    const {animate: animateSecond}  = createDropAnimation(secondLetter, 1000, 40)
    const {animate: animateThird}  = createDropAnimation(thirdLetter, 3000, 20)

    const renderer = () => {
        animateFirst()
        animateSecond()
        animateThird()
    }

    render(renderer)
}


function render(renderFn) {
    const rafHandler = () => {
        renderFn()
        requestAnimationFrame(rafHandler);
    }

    requestAnimationFrame(rafHandler)
}

function createDropAnimation(element, startDelay = 0, gravityAcceleration = 10) {
    const startTime = Date.now() + startDelay
    const maxHeight = parseInt(getComputedStyle(element).bottom, 10)
    let currentHeight = maxHeight
    let prevTime = null
    let speed = 0

    const animate = () => {
        const currentTime = Date.now()
        if (startTime > currentTime) {
            return
        }

        if (!prevTime) {
            prevTime = currentTime
        }

        const deltaTime = (currentTime - prevTime) / 1000
        speed += deltaTime * (-gravityAcceleration)
        const deltaY = speed * deltaTime
        currentHeight += deltaY

        const clampedH =  clamp(currentHeight, 0, maxHeight)
        if (clampedH === 0 || clampedH === maxHeight) {
            speed = -speed
        }

        element.setAttribute('style', `bottom: ${clampedH}px`);
        prevTime = currentTime
    }

    return {
        animate,
    }
}

function clamp(value, min, max) {
    return Math.min(Math.max(value, min), max)
}
