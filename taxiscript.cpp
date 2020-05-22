taxicall = array();

command taxi(rsn) {
	permission = "taxi.call";
	execute() {
		if (taxicall.contains(player.id) == false) {
			reason = "None";
			if (isSet(rsn)) { reason = str.join(" ", arguments); }

			foreach(taxi in server.players) {
				if (taxi.hasPermission("taxi")) { taxi.message(player.name + " has called a taxi. Destination: " + reason + ". Accept this job? /accept"); }
			}
			taxicall.add(player.id);
			player.message("You have already called a taxi!");
			wait.seconds(60, waitRemove(player.id));
		}
		else { player.message("You have already called a taxi!"); }
	}
}

command respond() {
	permission = "taxi";
	execute() {
		if (player.hasPermission("taxi")) {
			if (taxicall[0] != null) {
				targetPlayer = toPlayer(taxicall[0]);
				if (isPlayer(targetPlayer)) {
					targetName = targetPlayer.name;
					location = targetPlayer.position;
					player.setMarker(location);
					taxicall.remove(targetPlayer.id);
 
					foreach(taxi in server.players) {
						if (taxi.hasPermission("taxi")) { taxi.message(player.name + " has accepted " + targetName + " call!"); }
					}

					player.message("Placed a marker on " + targetName + " location!");
					targetPlayer.message(player.name + " has accepted your request, they are making their way to you now!");
				}
				else { player.message("No calls to answer!"); }
			}
			else { player.message("No calls to answer!"); }
		}
		else { player.message("You aren't a taxi driver!"); }
	}
}

command responds() {
	permission = "taxi";
	execute() {
		responds = toInt(taxicall.count);
		player.message("Pending jobs: " + responds);
	}
}

command taxihelp() {
	permission = "taxi";
	execute() {
		player.message("Taxi Commands");
		player.message("/taxihelp = Shows all the commands related to Taxis.");
		player.message("/respond = Allows drivers to accept calls. First come first serve.");
		player.message("/responds = Displays all pending jobs.");
	}
}

function waitRemove(myPlayer) {
	playerRemove = toPlayer(myPlayer);
	if (isPlayer(playerRemove) {
		if (taxicall.contains(playerRemove.id) {
			taxicall.remove(playerRemove.id);
				playerRemove.message("No taxi drivers accepted your job. Feel free to send another now.");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO TAXI ORDERS
/////////////////////////////////////////////////////////////////////////////////////////
command acceptOrder(requestID) {
	execute() {
		if (isSet(requestID)) {
			Result = database.execute("SELECT * FROM taxiRequest WHERE id = '" + requestID + "';");

			if (Result.count != 0) {
				ResultArray = Result[0];
				requestName = ResultArray[1];
				requestLocation = ResultArray[2];
				requestaccepted = ResultArray[3];

				if (requestaccepted == "False") {
					logger.log("acceptOrder - requestaccepted returned 'False'");
				}
				else {
					logger.log("acceptOrder - requestaccepted returned something different than 'False'");
				}
			}
		}
	}
}
command orderTaxi() {
	//permission = "taxi.call";
	execute() {

		playerID = player.id;
		playerName = player.name;
		positionX = player.position.x;
		positionY = player.position.y;
		positionZ = player.position.z;
		saveToDBPos = toString(positionX) + "," + toString(positionY) + "," + toString(positionZ);
		Result = database.execute("SELECT * FROM taxiRequest WHERE steamID64 = '" + playerID + "';");

		if (Result.count != 0) {
			player.message(str.format("<color=red>You have already called a Taxi!</color>"));
		}
		else {
			player.message(str.format("<color=red>You have ordered a Taxi!</color>"));
			database.execute("INSERT INTO taxiRequest (requestName, requestLocation) VALUES ('" + playerName + "', '" + saveToDBPos + "');");
		}

		foreach(x in server.players) {
			//if (taxi.hasPermission("taxiDriver")) { taxi.message(player.name + " has called a taxi. Destination: " + reason + ". Accept this job? /accept"); }
			if (x.hasPermission("taxi.job")) { //change that to permissions once created.
				taxiDriver.message(str.format("<color=yellow>A new order has been made!</color>", player.name));
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO TAXI ORDERS END
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// HELP COMMAND
/////////////////////////////////////////////////////////////////////////////////////////
command taxiHelp() {
	//permission = "taxi.help";
	execute() {
		player.message(str.format("<color=cyan>/joinTaxi to get a job as Taxi Driver</color>", requestID, requestName));
		player.message(str.format("<color=cyan>/quitTaxi to quit the job as Taxi Driver.</color>", requestID, requestName));
		player.message(str.format("<color=cyan>/taxirequests lists all Taxi orders</color>", requestID, requestName));
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// HELP COMMAND END
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO ACCEPTING AN ORDER END
/////////////////////////////////////////////////////////////////////////////////////////
command taxiRequests() {
	permission = "taxi.job";
	execute() {
		Result = database.execute("SELECT * FROM taxiRequest WHERE accepted = '" + 0 + "';");

		foreach(request in Result)
		{
			requestID = request[0];
			requestName = request[1];
			requestLocation = request[2];
			// maybe we could use the requset position to get the nearest location in the loop
			// so the taxidriver gets that message:
			// Request #1 by Radona near Pudget Sound.

			player.message(str.format("<color=cyan>Request #{0} by {1}</color>", requestID, requestName));

			// Need to edit that with nearest location.
			//player.message(str.format("<color=cyan>Request #{0} by {1} near {2}.</color>", requestID, requestName, getNearestLocation(<vector3>)));
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO ACCEPTING AN ORDER END
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO GETTING OR QUITTING THE JOB
/////////////////////////////////////////////////////////////////////////////////////////
command joinTaxi() {
	permission = "taxi.job";
	execute() {
		playerID = player.id;
		Result = database.execute("SELECT * FROM taxiDriver WHERE steamID64 = '" + playerID + "';");

		if (Result.count != 0) {
			player.message(str.format("<color=yellow>Would you like to apply as a taxi driver?</color>"));
			player.message(str.format("<color=yellow>Please confirm with /applyConfirm</color>"));
			player.setData("joinTaxi", true);
		}
		else {
			player.message(str.format("<color=yellow>You're already a Taxi Driver.</color>"));
		}
	}
}

command applyconfirm() {
	permission = "taxi.job";
	execute() {
		if (player.getData("joinTaxi")) {

			playerID = player.id;
			playerName = player.name;

			database.execute("INSERT INTO taxiDriver (steamID64, taxiDriverName) VALUES ('" + playerID + "', '" + playerName + "');");
			player.message(str.format("<color=yellow>You are now a Taxi Driver!</color>"));

		}
		else {
			player.message(str.format("<color=yellow>Please use /joinTaxi to apply to be a taxi driver</color>"));
		}
	}
}

command quitTaxi() {
	permission = "taxi.job";
	execute() {
		playerID = player.id;
		Result = database.execute("SELECT * FROM taxiDriver WHERE steamID64 = '" + playerID + "';");

		if (Result.count != 0) {
			player.message(str.format("<color=yellow>Do you want to quit your job as a Taxi Driver?</color>"));
			player.message(str.format("<color=yellow>Please confirm with /quitConfirm</color>"));
			player.setData("quitTaxi", true);
		}
		else {
			// we dont need a warning if they want to quit a job that they are not having lol.
			player.message(str.format("<color=yellow>Are you sure you want to quit your job while youre not even having a job?</color>"));
		}
	}
}

command quitconfirm() {
	permission = "taxi.job";
	execute() {
		if (player.getData("quitTaxi")) {
			player.message(str.format("<color=yellow>You have quit your job as Taxi Driver.</color>"));
			database.execute("DELETE FROM taxiDriver WHERE steamID64 = '" + playerID + "';");
		}
		else {
			// we dont need a warning if they want to quit a job that they are not having lol.
			// could be a nice easter egg, though.
			player.message(str.format("<color=yellow>Error: Cant quit a job you dont have!11!! The Devs are watching you.. </color>"));
		}
	}
}

event onPlayerJoined(player) {
	playerID = player.ID;
	Result = database.execute("SELECT * FROM taxiDriver WHERE steamID64 = '" + playerID + "';");

	if (Result.count != 0) {
		player.addGroup("TaxiDriver");
		player.message(str.format("<color=yellow>Welcome back! You are back on your job as TaxiDriver."));
	}
}

event onPlayerQuit(player) {
	playerID = player.ID;
	Result = database.execute("SELECT * FROM taxiDriver WHERE steamID64 = '" + playerID + "';");

	if (Result.count != 0) {
		player.removeGroup("TaxiDriver"); //to avoid errors if groups persist.
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO GETTING OR QUITTING THE JOB END
/////////////////////////////////////////////////////////////////////////////////////////