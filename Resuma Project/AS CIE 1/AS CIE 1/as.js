let slide=document.querySelectorAll(".patientReview");
let connectBtn= document.getElementById("connectBtn")
let count = 0;

 slide.forEach(function(slides, index){
    slides.style.left=`${index * 100}%`
 })

 function myfun(){
    slide.forEach(function(curVal){
        curVal.style.transform=`translateX(-${count * 100}%)`
    })
 }
 setInterval(function(){
    count++;
if(count==slide.length){
    count=0;
}
    myfun()
 },2000)

 connectBtn.addEventListener("click",function(){
    let email=document.getElementById("email")
    let pass=document.getElementById("pass")
    if(email.value==""&& pass.value==""){
    alert("Enter Details")
}else{
      alert("you logged in")  
    }}
    )
