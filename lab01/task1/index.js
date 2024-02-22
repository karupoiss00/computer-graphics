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
    const STEP_COUNTS = 50000 * (1 / gravityAcceleration)
    const HALF_STEPS_COUNT = STEP_COUNTS / 2
    const startTime = Date.now() + startDelay
    let height = parseInt(getComputedStyle(element).bottom, 10)

    return {
        animate: () => {
            if (startTime > Date.now())
            {
                return
            }

            let step = (Date.now() - startTime) % STEP_COUNTS;

            if (step > HALF_STEPS_COUNT)
            {
                step = STEP_COUNTS - step
            }

            const wave = Math.cos(step / HALF_STEPS_COUNT * Math.PI);
            const resultH = Math.abs(wave) * height

            element.setAttribute('style', `bottom: ${resultH}px`);
        },
    }
}