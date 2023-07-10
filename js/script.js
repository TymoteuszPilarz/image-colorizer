// had to do many unconventional things
// executing JS in WT is somewhat fragile

// linking fonts

var head = document.head || document.getElementsByTagName('head')[0];

var link1 = document.createElement('link');
link1.rel = 'preconnect';
link1.href = 'https://fonts.googleapis.com';
head.appendChild(link1);

var link2 = document.createElement('link');
link2.rel = 'preconnect';
link2.href = 'https://fonts.gstatic.com';
link2.setAttribute('crossorigin', '');
head.appendChild(link2);

var link3 = document.createElement('link');
link3.href = 'https://fonts.googleapis.com/css2?family=Pattaya&display=swap';
link3.rel = 'stylesheet';
head.appendChild(link3);

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

// Adding page title and logo

var toolbar = document.getElementsByClassName("toolbar")[0];


var colorArray = ["darkred", "cyan", "yellow", "darkgreen", "coral", "magenta",
    "deeppink", "lawngreen", "lime", "navy", "olive", "orange", "purple"]
var titleHTML = "Image"
var colorizer = "Colorizer"

// wanted to make random colors but didnt work
for (i = 0; i < colorizer.length; i++) {
    letter = colorizer[i];
    color = colorArray[i];

    string = "<span style=\"font-size: 26px; color:" + color + "\">" + letter + "</span>";
    titleHTML = titleHTML + string;
}

// didnt work with css, hat to make it inline
var pageTitle = document.createElement("div");
pageTitle.className = "page-title";
pageTitle.innerHTML = titleHTML;
pageTitle.style.fontSize = '26px';
pageTitle.style.fontFamily = 'Pattaya, sans-serif';
pageTitle.style.color = "darkgrey";
pageTitle.style.alignSelf = "center"
pageTitle.style.margin = "8px"


var logo = document.createElement("img");
logo.className = "logo"
logo.src = "../favicon.ico";
logo.style.margin = "6px";

logo.addEventListener("mouseenter", () => {
    logo.style.transform = "rotate(-10deg) scale(1.1)"
})
logo.addEventListener("mouseleave", () => {
    logo.style.transform = "rotate(10deg) scale(0.9)"
})

toolbar.insertBefore(logo, toolbar.firstChild);
toolbar.insertBefore(pageTitle, logo);