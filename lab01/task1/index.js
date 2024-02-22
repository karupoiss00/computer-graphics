window.onload = main

function main() {
    const firstLetter = document.body.getElementsByClassName('g-letter')[0]
    const secondLetter = document.body.getElementsByClassName('r-letter')[0]
    const thirdLetter = document.body.getElementsByClassName('m-letter')[0]

    if (!firstLetter || !secondLetter || !thirdLetter) {
        throw new Error('one of letter elements is undefined')
    }

    const {animate: animateFirst} = createDropAnimation(firstLetter, 5000/*, 20*/)
    const {animate: animateSecond}  = createDropAnimation(secondLetter, 1000)
    const {animate: animateThird}  = createDropAnimation(thirdLetter, 3000/*, 30*/)

    const rafLoop = () => {
        animateFirst()
        animateSecond()
        animateThird()
        requestAnimationFrame(rafLoop)
    }

    requestAnimationFrame(rafLoop)
}

function createDropAnimation(element, startDelay = 0, gravityAcceleration = 10) {
    const stepsCount = 50000 * (1 / gravityAcceleration)
    const startTime = Date.now() + startDelay
    let height = parseInt(getComputedStyle(element).bottom, 10)

    return {
        animate: () => {
            if (startTime > Date.now())
            {
                return
            }

            const wave = calculateWaveFactor(startTime, stepsCount)
            const resultH = Math.abs(wave) * height

            element.setAttribute('style', `bottom: ${resultH}px`);
        },
    }
}

function calculateWaveFactor(startTime, stepsCount) {
    const HALF_STEPS_COUNT = stepsCount / 2
    let step = (Date.now() - startTime) % stepsCount;

    if (step > HALF_STEPS_COUNT)
    {
        step = stepsCount - step
    }

    return Math.cos(step / HALF_STEPS_COUNT * Math.PI);
}