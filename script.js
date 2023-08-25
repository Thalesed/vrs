const gallery = document.querySelector('.gallery');
const slides = document.querySelectorAll('.slide');
let currentIndex = 0;

document.addEventListener('keydown', handleKeydown);

function handleKeydown(event) {
    if (event.key === 'ArrowLeft') {
        showSlide(currentIndex - 1);
    } else if (event.key === 'ArrowRight') {
        showSlide(currentIndex + 1);
    }
}

function showSlide(index) {
    if (index < 0) {
        index = slides.length - 1;
    } else if (index >= slides.length) {
        index = 0;
    }
    
    slides[currentIndex].classList.remove('active');
    slides[index].classList.add('active');
    
    currentIndex = index;
}

showSlide(currentIndex);  // Show the initial slide
