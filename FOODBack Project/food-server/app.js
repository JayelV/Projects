var express = require('express');
var bodyParser = require('body-parser');
const { Pool } = require('pg');

var app = express();

app.use(bodyParser.urlencoded({ extended: true }))

// variables to be manipulated by buttons

let count = 0;
let namesList = [];
let uid = null;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// HANDLE VOTINGS::::::::::::::::::::::::::::::::::::;;

app.put('/votes', (request, response) => {
	let uid = request.body.uid;
	let cid = request.body.cid;
    console.log("SELECT response FROM votes WHERE cid = $1 AND uid = $2", [cid, uid]);
    pool.query("SELECT response FROM votes WHERE cid = $1 AND uid = $2", [cid, uid])
    .then(res => {
	    console.log('DB response: ' + res.rows[0]);
		if (res == null) {
			console.log('RES IS NULL')
		}
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

app.put('/votes/update', (request, response) => {
	let cid = request.body.cid;
	let votes = request.body.votes;
	console.log("VOTES: ---------------- " + votes)

	console.log("updating votes to: " + votes);

    console.log("UPDATE comments set votes = $2 WHERE cid = $1", [cid, votes]);
    pool.query("UPDATE comments set votes = $2 WHERE cid = $1", [cid, votes])
    .then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

app.post('/votes/add', (request, response) => {
	let cid = request.body.cid;
	let uid = request.body.uid;
	let vote = request.body.response;
	
    console.log("INSERT INTO votes (cid, uid, response) VALUES ($1, $2, $3)", [cid, uid, vote]);
    pool.query("INSERT INTO votes (cid, uid, response) VALUES ($1, $2, $3)", [cid, uid, vote])
    .then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

app.put('/votes/switch', (request, response) => {
	let cid = request.body.cid;
	let uid = request.body.uid;
	let vote = request.body.response;

    console.log("UPDATE votes set response = $2 WHERE cid = $1 AND uid = $3", [cid, vote, uid]);
    pool.query("UPDATE votes set response = $2 WHERE cid = $1 AND uid = $3", [cid, vote, uid])
    .then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

app.delete('/votes/remove', (request, response) => {
    let cid = request.body.cid;
	let uid = request.body.uid;

    console.log(`Got request to delete matching comments, will remove ${cid} from database`);
    pool.query('DELETE FROM votes WHERE cid = $1 AND uid = $2', [cid, uid])
	.then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.sendStatus(200)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})





//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// handle requests

app.get('/hot_at_cage', (request, response) => {
    console.log(`Got request for hot_at_cage items`);
    pool.query(" SELECT DISTINCT item from cagemenu where category = 'food/sandwich' FETCH FIRST 3 ROWS ONLY") // 3 foods, and three bevs. 
	.then(res => {
	    let arr = [];
	    console.log('DB response: ');
		
	    res.rows.forEach(val => {

			console.log(val);
			arr.push(val);
	    });
	    response.send(arr)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})


// RETRIEVE count - send value of first row of button_count table

app.get('/uid', (request, response) => {
    console.log(`Got request for uid, `);
    pool.query("SELECT uid FROM users WHERE username = 'Inna' AND pin = '3456'")
	.then(res => {
	    console.log('DB response: ' + res.rows[0]);
		uid = res.rows[0];
		console.log('userid: ' + uid);
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

app.put('/login', (request, response) => {
	let login_info = request.body.login_info;
    let data = login_info.split(',');
    console.log("SELECT COUNT(*) FROM users WHERE username = $1 AND pin = $2", [data[0],data[1]]);
    pool.query("SELECT uid FROM users WHERE username = $1 AND pin = $2", [data[0],data[1]])
    .then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

/* REGISTRATION */
app.post('/register', (request, response) => {
	// let login_info = request.body.login_info;
    // let data = login_info.split(',');
	let username = request.body.username;
	let pin = request.body.pin;
	//pool.query('INSERT INTO comments (comment, neg_feedback) VALUES ($1, $2)', [comment, fb])

    console.log("INSERT INTO users (username, pin) VALUES ($1, $2)", [username, pin]);
    pool.query("INSERT INTO users (username, pin) VALUES ($1, $2)", [username, pin])
    .then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.send(res.rows[0]);
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

// RETRIEVE comments - send array of all names in button_names table

app.get('/comments', (request, response) => {
    console.log(`Got request for comments`);
    pool.query('SELECT comment, date, votes, neg_feedback, uid, cid FROM comments ORDER BY votes desc')
	.then(res => {
	    let arr = [];
	    console.log('DB response: ');
		
	    res.rows.forEach(val => {

			console.log(val);
			arr.push(val);
	    });
	    response.send(arr)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

// RETRIEVE photos - send array of all names in button_names table

app.get('/photos', (request, response) => {
    console.log(`Got request for all photos`);
    pool.query('SELECT * FROM photos ORDER BY pid desc')
	.then(res => {
	    let arr = [];
	    console.log('DB response: ');
		
	    res.rows.forEach(val => {

			console.log(val);
			arr.push(val);
	    });
	    response.send(arr)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

// CREATE names - insert a name into button_names table
// body parameters:
//	name	string	name value to be inserted

app.post('/comments', (request, response) => {
    let comment = request.body.comment;
	let fb = request.body.feedback;
	let userid = request.body.uid;
	if (fb == 'false') {
		fb = 'green';
	} else { fb = 'red'; }

    console.log(request.body)
    console.log(request.body.comment)
    console.log(`Got request to add a comment, will add ${comment} to database`);
    pool.query('INSERT INTO comments (comment, neg_feedback, uid) VALUES ($1, $2, $3)', [comment, fb, userid])
	.then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.sendStatus(200)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

// CREATE photo posts
app.post('/photos', (request, response) => {
    let url = request.body.url;
	let userid = request.body.uid;

    console.log(`Got request to add a photo, will add ${url} to database`);
    pool.query('INSERT INTO photos (url, uid) VALUES ($1, $2)', [url, userid])
	.then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.sendStatus(200)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})


//;
app.get('/green/red', (request, response) => {
    console.log(`Got request for green and red`);
    pool.query('select neg_feedback, COUNT(*) FROM comments GROUP BY neg_feedback')
	.then(res => {
	    let arr = [];
	    console.log('DB response: ');
	    res.rows.forEach(val => {
		console.log(val);
		arr.push(val.neg_feedback + '|' + val.count);
	    });
	    response.send({name_val: arr})
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})


// DELETE names - delete all rows of button_names table with matching names
// body parameters:
//	name	string	name value to be deleted


app.delete('/comments', (request, response) => {
    let cid = request.body.cid;
    console.log(`Got request to delete matching comments, will remove ${cid} from database`);
    pool.query('DELETE FROM comments WHERE cid = $1', [cid])
	.then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.sendStatus(200)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

app.delete('/photos', (request, response) => {
    let pid = request.body.pid;
    
    console.log(`Got request to delete matching photo, will remove ${pid} from database`);
    pool.query('DELETE FROM photos WHERE pid = $1', [pid])
	.then(res => {
	    console.log('DB response: ' + res.rows[0]);
	    response.sendStatus(200)
	})
	.catch(err =>
	       setImmediate(() => {
		   throw err;
	       }));
})

// catch 404 and forward to error handler

app.use(function(request, response, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handler
app.use(function(err, request, response, next) {
  // set locals, only providing error in development
  response.locals.message = err.message;
  response.locals.error = request.app.get('env') === 'development' ? err : {};

  // render the error page
  response.status(err.status || 500);
});


/* Main program */

console.log(`Starting button-server-db app`);

const lib = require('./mcalib');
lib.setErrorPrefix(__filename);  // set label for lib error messages

// database connection parameters
const dbHost = "anansi.stolaf.edu";
const user = 'versoz1';    // CHANGE to your username, e.g., jones1
const password = lib.getPGPassword(dbHost);  // uncomment for Windows
const dbName = 'mca_f21';
const schema = 'mca_f21_food';  // CHANGE to your username as schema for Lab 5
                       // CHANGE to team schema for project

const pool = new Pool({
    user: user,
    password: password,                      // uncomment for Windows
    host: dbHost,
    database: dbName,
    port: 5432,
});

pool.on('connect', client => {
    client.query(`SET search_path = ${schema}, public;`)
});

pool.on('error', (err, client) => {
  console.error('Unexpected error on idle client', err)
  process.exit(-1)
})

console.log(`Connected to database ${dbName} on ${dbHost}`);

console.log("IP addresses:  ", lib.getIPAddresses());

module.exports = app;


//async, await 