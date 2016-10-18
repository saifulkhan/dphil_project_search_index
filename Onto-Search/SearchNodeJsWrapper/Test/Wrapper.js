var d = require('domain').create();

// Load the http module to create an http server.
var http = require('http');
var fs = require('fs');
var url = require('url');
//var express = require('/usr/local/bin/express');
//var app = express();
//var body_parser = require('/opt/node/current/lib/node_modules/body-parser');
var addon = require("../build/Release/QueryProcessorAddon");



var obj = new addon.QueryProcessorWrapper();
/*
console.log( obj.search(" hello from client!") );
*/

var jsonstring = obj.treemapBuild(150, 150, 800, 400, function(data){
 console.log("treemapBuild()", data);
});

jsonstring = obj.treemapData(3, function(data){
 console.log("treemapData()", data);
});


jsonstring = obj.treemapData(4, function(data){
 console.log("treemapData()", data);
});


jsonstring = obj.treemapData(5, function(data){
 console.log("treemapData()", data);
});



jsonstring = obj.search("draft", function(data){
 console.log("search()", data);
});

/*
//console.log(treemapBuild);
console.log("Received JSON data from query processor.")
var jsonvar = JSON.parse(jsonstring);
console.log(jsonvar);
console.log("Received JSON data from query processor. End...")
*/
/*
  var jsonstring = obj.treemapBuild(150, 150, 200, 200);

  obj.treemapBuild(150, 150, 200, 200, function(jsonstring) {

  });

/*

//  response.end(addon.FetchNodeList("Commandlinearguments"));
addon.buildTreemap(width, height, x, y, function(msg) {
    console.log(msg);
    response.end(msg);
  });


//  response.end(addon.FetchNodeList("Commandlinearguments"));
addon.getTreemap(depth, function(msg) {
    console.log(msg);
    response.end(msg);
  });



app.use(body_parser.urlencoded());

app.get('/', function (request, response) {
  console.log("Sending...");
  //console.log(request.query['width']);
  fs.readFile('./index.html', function(err, data) {
    response.end(data);
  });

});

app.get('/window_size', function (request, response) {
  var width = request.query['width'];
  var height = request.query['height'];
  console.log("Width:"+width);
  console.log("Height:"+height);
});






app.get('/json_data', function (request, response) {
  console.log("Sending json data...");
  //console.log(request.query['width']);
  fs.readFile('./data.json', function(err, data) {
    response.end(data);
  });

});



app.listen(8080);


// Put a friendly message on the terminal
console.log("Server running at http://127.0.0.1:8080/");
*/



