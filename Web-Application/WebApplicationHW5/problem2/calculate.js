var unit
function calculate()
{
    console.log(unit);
    var shape=document.getElementById("shape");
    console.log(shape.value);
    var r=document.getElementById("radius");
    console.log(r.value);
    var h=document.getElementById("height");
    console.log(h.value);
    var v;
    var pi=3.1415926;
    if (unit==0)
    {
        document.getElementById("phase_1").innerHTML = "You choose to use English units";
        document.getElementById("2-2").innerHTML = "(ft)";
        document.getElementById("2-3").innerHTML = "(ft)";
        document.getElementById("2-4").innerHTML = "(ft^3)";
    }
    else if (unit==1)
    {
        document.getElementById("phase_1").innerHTML = "You choose to use SI units";
        document.getElementById("2-2").innerHTML = "(m)";
        document.getElementById("2-3").innerHTML = "(m)";
        document.getElementById("2-4").innerHTML = "(m^3)";
    }
    else
    {
        alert("Please choose unit first");
        location.reload();
    }
    switch(Number(shape.value))
    {
        case 1:
            v=pi*Math.pow(r.value,2)*h.value;
            document.getElementById("phase_2").innerHTML = "You choose to find the volume of Cylinder";
            document.getElementById("3-1").innerHTML = "Cylinder";
            document.getElementById("3-2").innerHTML = r.value;
            document.getElementById("3-3").innerHTML = h.value;
            document.getElementById("3-4").innerHTML = v;
            break;
        case 2:
            v=pi*Math.pow(r.value,2)*h.value/3;
            document.getElementById("phase_2").innerHTML = "You choose to find the volume of Cone";
            document.getElementById("3-1").innerHTML = "Cone";
            document.getElementById("3-2").innerHTML = r.value;
            document.getElementById("3-3").innerHTML = h.value;
            document.getElementById("3-4").innerHTML = v;
            break;
        case 3:
            v=4/3*pi*Math.pow(r.value,2);
            document.getElementById("phase_2").innerHTML = "You choose to find the volume of Sphere";
            document.getElementById("3-1").innerHTML = "Sphere";
            document.getElementById("3-2").innerHTML = r.value;
            document.getElementById("3-3").innerHTML = " ";
            document.getElementById("3-4").innerHTML = v;
            break;
        default:
            alert("Please choose shape ");
            //location.reload();
    }
}
function getvalue(value)
{
	unit=value
}