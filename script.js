'use strict';

// Selecting elements
const score0El = document.querySelector('#score--0');
const score1El = document.getElementById('score--1');
const diceEl = document.querySelector('.dice');
const btnNew = document.querySelector('.btn--new');
const btnRoll = document.querySelector('.btn--roll');
const btnHold = document.querySelector('.btn--hold');
const currentScoreElP1 = document.querySelector('#current--0');
const currentScoreElP2 = document.querySelector('#current--1');

score0El.textContent = 0;
score1El.textContent = 0;
// diceEl.classList.add('hidden');

let currentScore = 0;
let activePlayer = 0;

changePlayer();

const gameSet = 5;
let player1Score = 0;
let player2Score = 0;

// Checks to see if player has won the game
const checkWinner = function () {
  if (player1Score >= gameSet || player2Score >= gameSet) {
    btnHold.disabled = true;
    btnRoll.disabled = true;
    return true;
  }
};

// Changes the active player (white-background)
function changePlayer() {
  // Applying to both of them to ensure only one of them has the class
  document
    .querySelector(`.player--${activePlayer === 0 ? 0 : 1}`)
    .classList.add('player--active');
  document
    .querySelector(`.player--${activePlayer === 0 ? 1 : 0}`)
    .classList.remove('player--active');
}

// Starts a new game
function resetGame() {
  // Turns off the black bg color
  document
    .querySelector(`.player--${activePlayer === 0 ? 1 : 0}`)
    .classList.remove('player--winner');
  player1Score = 0;
  player2Score = 0;
  activePlayer = 0;
  btnHold.disabled = false;
  btnRoll.disabled = false;
  score0El.textContent = 0;
  score1El.textContent = 0;
  currentScoreElP1.textContent = 0;
  currentScoreElP2.textContent = 0;
  changePlayer();
}

// Updates current score
function updateScore() {
  document.getElementById(`current--${activePlayer}`).textContent =
    currentScore;
}

// Rolling dice functionality

btnRoll.addEventListener('click', function () {
  // 1. Generating random dice roll (from one to 6)
  const dice = Math.trunc(Math.random() * 6) + 1;
  // 2. Display dice
  // diceEl.classList.remove('hidden');
  diceEl.src = `dice-${dice}.png`;
  // 3. Check for rolled 1: If true, switch to next player
  if (dice !== 1) {
    currentScore += dice;
    updateScore();
    checkWinner();
    // 4. Swicth to next player
  } else {
    currentScore = 0;
    updateScore();
    activePlayer = activePlayer === 0 ? 1 : 0;
    changePlayer();
  }
});

btnHold.addEventListener('click', function () {
  document.getElementById(`current--${activePlayer}`).textContent = 0;
  document.getElementById(`current--${activePlayer}`).textContent = 0;

  if (activePlayer === 0) {
    player1Score += currentScore;
    score0El.textContent = player1Score;
  } else {
    player2Score += currentScore;
    score1El.textContent = player2Score;
  }

  checkWinner();
  activePlayer = activePlayer === 0 ? 1 : 0;
  currentScore = 0;
  if (checkWinner()) {
    document.getElementById(
      `score--${activePlayer === 0 ? 1 : 0}`
    ).textContent = 'WINS';
    document
      .querySelector(`.player--${activePlayer === 0 ? 1 : 0}`)
      .classList.add('player--winner');
  } else {
    changePlayer();
  }
});

btnNew.addEventListener('click', resetGame);
