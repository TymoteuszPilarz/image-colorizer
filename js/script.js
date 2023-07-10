// had to do many unconventional things
// executing JS in WT is somewhat fragile

// playng audio on button click

// weird, JS Audio class didn't work for some reason, had to make it via HTML element
var clickSound = document.createElement('audio');
clickSound.src = "../sound/click1.wav";

// creating list of all desired elements
classList = ["options-button", "color-picker", "colorize-button"];
var elementsToAddClickSound = [];
  
for (var i = 0; i < classList.length; i++) {
    var currentClass = classList[i];
    var classElements = document.getElementsByClassName(currentClass);
    
    for (var j = 0; j < classElements.length; j++) {
        elementsToAddClickSound.push(classElements[j]);
    }
  }

// adding on-click listener
elementsToAddClickSound.forEach(element => {
    element.addEventListener("click", () => {
        clickSound.play();
    })
});

// simillarly adding swoosh sound on dropdowns

var hoverSound = document.createElement('audio');
hoverSound.src = "../sound/swoosh1.wav";

var dropDowns = document.getElementsByClassName("dropdown");

// for some reason forEach loop doesn't work
for(i = 0; i < dropDowns.length; i++) {
    dropDowns[i].addEventListener("mouseover", () => {
        hoverSound.play();
    })
}