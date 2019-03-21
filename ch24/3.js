
var p = prompt("password?", "");
while(p !== "5265") 
{
	p = prompt("password?", "");
}
if(p == "5265") 
{
	alert("Welcome!");
	document.write("<h1>"+"Welcome!"+"</h1>");
}