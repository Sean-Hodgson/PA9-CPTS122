var express = require('express');
var app = express();
var fs = require("fs");

var count = 0;

app.get('/nPlayer', function (req, res) {
    // First read existing users.
   count += 1; 
   res.status(201).send({playerCount: count});
 })

 app.get('/Players', function (req, res) {
    // First read existing users.
   res.status(201).send({playerCount: count});
 })

 app.get('/dPlayer', function (req, res) {
    // First read existing users.
   count -= 1; 

   if (count == -1)
   {
      count = 0;
   }

   res.status(201).send({playerCount: count});
 })

var server = app.listen(process.env.PORT, function () {
   var host = server.address().address
   var port = server.address().port
   console.log("Example app listening at http://%s:%s", host, port)
})
