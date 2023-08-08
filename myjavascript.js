
//Manual
const btnOn = document.getElementById("btnOnId_01");
const btnOff = document.getElementById("btnOffId_01");
const pumper = document.getElementById('pumper');
const autoContainer = document.getElementById('autoContainer');

btnOn.onclick = function(){
    document.getElementById("denId_01").src = "./img/water.jpg"
    pumper.value = '1';
}

btnOff.onclick = function(){
  document.getElementById("denId_01").src = "./img/nonWater.jpg"
  pumper.value = '0';

}

function Close()
{
  pumper.value = '3';
}




