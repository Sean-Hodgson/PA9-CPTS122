var express = require('express');
var app = express();
var fs = require("fs");

var count = 1;

app.get('/nPlayer', function (req, res) {
    // First read existing users.
   count += 1; 
   res.status(201).send({playerCount: count});
 })

 app.get('/dPlayer', function (req, res) {
    // First read existing users.
   count -= 1; 
   res.status(201).send({playerCount: count});
 })

 

var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port
   console.log("Example app listening at http://%s:%s", host, port)
})