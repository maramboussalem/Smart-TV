let score = 0;
let currentIsland = 1;
let currentQuestion = 0;
const questions = {
    1: [
        { text: "Quelle est la capitale de la France ?", answers: ["Paris", "Londres", "Berlin", "Madrid"], correct: 1 },
        { text: "2 + 2 = ?", answers: ["3", "4", "5", "6"], correct: 2 }
    ],
    2: [
        { text: "Quel est le plus grand océan ?", answers: ["Atlantique", "Pacifique", "Indien", "Arctique"], correct: 2 }
    ],
    3: [
        { text: "Quelle est la couleur du ciel ?", answers: ["Bleu", "Vert", "Rouge", "Jaune"], correct: 1 }
    ]
};

function playSound(type) {
    const sounds = {
        click: new Audio('https://cdn.pixabay.com/audio/2022/03/10/audio_7e351e7e8a.mp3'),
        correct: new Audio('https://cdn.pixabay.com/audio/2022/03/10/audio_4b6e8c7e8b.mp3')
    };
    if (sounds[type]) sounds[type].play().catch(() => {});
}

function launchConfetti() {
    confetti({
        particleCount: 150,
        spread: 80,
        origin: { y: 0.5 },
        colors: ['#FFD700', '#FF6F61', '#40E0D0', '#ADFF2F', '#00B7EB']
    });
}

function selectAvatar(img) {
    document.querySelectorAll('.avatar-selection img').forEach(i => i.classList.remove('selected'));
    img.classList.add('selected');
    playSound('click');
}

function joinQuiz() {
    const code = document.getElementById('quiz-code').value;
    if (code) {
        window.location.href = 'quiz.html';
    } else {
        alert('Entre un code de quiz valide ! 🏝️');
    }
}

function generateQuizCode() {
    const code = Math.random().toString(36).substring(2, 8).toUpperCase();
    document.getElementById('generated-code').textContent = code;
    playSound('click');
}

function goToIsland(island) {
    currentIsland = island;
    currentQuestion = 0;
    document.querySelectorAll('.island').forEach((el, index) => {
        el.classList.toggle('completed', index < island - 1);
    });
    loadQuestion(currentIsland, currentQuestion);
    playSound('click');
}

function loadQuestion(island, questionIndex) {
    const question = questions[island][questionIndex];
    document.getElementById('category-name').textContent = `Île ${island}`;
    document.getElementById('question-number').textContent = questionIndex + 1;
    document.getElementById('question-text').textContent = question.text;
    for (let i = 1; i <= 4; i++) {
        document.getElementById(`answer${i}`).textContent = question.answers[i - 1];
    }
    document.querySelectorAll('input[name="answer"]').forEach(input => input.checked = false);
}

function submitAnswer() {
    const selectedAnswer = document.querySelector('input[name="answer"]:checked');
    if (selectedAnswer) {
        const question = questions[currentIsland][currentQuestion];
        if (parseInt(selectedAnswer.value) === question.correct) {
            score += 10;
            document.getElementById('score').textContent = score;
            alert('Bonne réponse ! 🎉');
            playSound('correct');
            launchConfetti();
        } else {
            alert('Oups, mauvaise réponse ! 😅 Tente encore !');
        }
        currentQuestion++;
        if (currentQuestion < questions[currentIsland].length) {
            loadQuestion(currentIsland, currentQuestion);
        } else {
            alert('Île terminée ! 🌴 Prêt pour la prochaine ?');
            if (currentIsland < 3) goToIsland(currentIsland + 1);
        }
    } else {
        alert('Choisis une réponse, aventurier ! 🏝️');
    }
}

// Initialisation pour la page quiz
if (window.location.pathname.includes('quiz.html')) {
    loadQuestion(currentIsland, currentQuestion);
}