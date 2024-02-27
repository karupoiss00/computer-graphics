window.onload = main

const DEFAULT_FRAME_RATE = 120

function main() {
    const firstLetter = document.body.getElementsByClassName('g-letter')[0]
    const secondLetter = document.body.getElementsByClassName('r-letter')[0]
    const thirdLetter = document.body.getElementsByClassName('m-letter')[0]

    if (!firstLetter || !secondLetter || !thirdLetter) {
        throw new Error('one of letter elements is undefined')
    }

    const {animate: animateFirst} = createDropAnimation(firstLetter, 2000, 400)
    const {animate: animateSecond}  = createDropAnimation(secondLetter, 1000, 500)
    const {animate: animateThird}  = createDropAnimation(thirdLetter, 3000, 300)

    const renderer = () => {
        animateFirst()
        animateSecond()
        animateThird()
    }

    render(renderer)
}


function render(renderFn, fpsRate = DEFAULT_FRAME_RATE) {
    const FRAME_PERIOD = 1000 / fpsRate
    let lastTime = null
    const rafHandler = (time) => {
        if (time - lastTime < FRAME_PERIOD) {
            requestAnimationFrame(rafHandler);
            return
        }

        lastTime = time;
        renderFn()
        requestAnimationFrame(rafHandler);
    }

    requestAnimationFrame(rafHandler)
}

function createDropAnimation(element, startDelay = 0, gravityAcceleration = 10) {
    const startTime = Date.now() + startDelay
    let height = parseInt(getComputedStyle(element).bottom, 10)
    let dropTime = Math.sqrt(2 * height / gravityAcceleration)
    let prevTime = Date.now() / 1000

    return {
        animate: () => {
            const currentTime = Date.now()
            if (startTime > currentTime) {
                return
            }

            const deltaTime = calculateStep(startTime, prevTime, dropTime)
            //console.log(deltaTime)
            const resultH = height - gravityAcceleration * (deltaTime ** 2) / 2

            element.setAttribute('style', `bottom: ${resultH}px`);
            prevTime = currentTime
        },
    }
}

function calculateStep(startTime, prevTime, dropTime) {
    const DOUBLE_TIME = dropTime * 2
    let step = (Date.now() - startTime) / 1000 % DOUBLE_TIME

    if (step > dropTime) {
        step = dropTime - (step - dropTime)
    }

    return step
}

function clamp(value, min, max) {
    return Math.min(Math.max(value, min), max)
}