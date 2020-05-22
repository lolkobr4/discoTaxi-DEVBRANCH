/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO TAXI ORDERS
/////////////////////////////////////////////////////////////////////////////////////////
command acceptOrder(requestID) {
	execute() {
		if (isSet(requestID)) {
			Result = database.execute("SELECT * FROM taxiRequest WHERE id = '" + requestID + "';");

			if (Result.count != 0) {
				ResultArray = Result[0];
				requestID = ResultArray[0];
				requestName = ResultArray[1];
				requestLocation = ResultArray[2];
				requestaccepted = ResultArray[3];

				if (requestaccepted == 0) {
					logger.log("acceptOrder - requestaccepted returned 'False'");
					database.execute("UPDATE taxiRequest SET accepted='1' WHERE id = '" + requestID + "';");
					player.message(str.format("<color=cyan>You have accepted {0}'s order!</color>", requestName));
				}
				else {
					logger.log("acceptOrder - requestaccepted returned something different than 'False'");
					player.message(str.format("<color=red>Order #{0} has already been accepted by someone else!</color>", requestID));
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
		Result = database.execute("SELECT * FROM taxiRequest WHERE requestName = '" + playerName + "';");

		if (Result.count != 0) {
			Result = database.execute("SELECT * FROM taxiRequest WHERE requestName = '" + playerName + "' AND accepted = 0;");
			if (Result.count != 0) {
				// Cant make a new order
				player.message(str.format("<color=red>You have already called a Taxi!</color>"));
			}
			else {
				//can make a new order.
				ResultArray = Result[0];
				requestID = ResultArray[0];
				requestName = ResultArray[1];
				requestLocation = ResultArray[2];
				requestaccepted = ResultArray[3];

				foreach(x in server.players) {
					//if (taxi.hasPermission("taxiDriver")) { taxi.message(player.name + " has called a taxi. Destination: " + reason + ". Accept this job? /accept"); }
					if (x.hasPermission("taxi.job")) { //change that to permissions once created.
						x.message(str.format("<color=yellow>A new order has been made!</color>", player.name));
					}
				}

				player.message(str.format("<color=yellow>You have ordered a Taxi!</color>"));
				database.execute("INSERT INTO taxiRequest (requestName, requestLocation) VALUES ('" + playerName + "', '" + saveToDBPos + "');");
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
		player.message(str.format("<color=cyan>/joinTaxi to get a job as Taxi Driver</color>"));
		player.message(str.format("<color=cyan>/quitTaxi to quit the job as Taxi Driver.</color>"));
		player.message(str.format("<color=cyan>/taxirequests lists all Taxi orders</color>"));
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
			player.message(str.format("<color=yellow>You're already a Taxi Driver.</color>"));

		}
		else {
			player.message(str.format("<color=yellow>Would you like to apply as a taxi driver?</color>"));
			player.message(str.format("<color=yellow>Please confirm with /applyConfirm</color>"));
			player.setData("joinTaxi", true);
		}
	}
}

command applyconfirm() {
	permission = "taxi.job";
	execute() {
		if (player.getData("joinTaxi") and player.getData("joinTaxi") != null) {

			playerID = player.id;
			playerName = player.name;

			database.execute("INSERT INTO taxiDriver (steamID64, taxiDriverName) VALUES ('" + playerID + "', '" + playerName + "');");
			player.message(str.format("<color=yellow>You are now a Taxi Driver!</color>"));
			player.setData("joinTaxi", false);
		}
		else {
			//player.message(str.format("<color=yellow>Please use /joinTaxi to apply to be a taxi driver</color>"));
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
		if (player.getData("quitTaxi") and player.getData("quitTaxi") != null) {
			playerID = player.id;
			player.message(str.format("<color=yellow>You have quit your job as Taxi Driver.</color>"));
			database.execute("DELETE FROM taxiDriver WHERE steamID64 = '" + playerID + "';");
			player.setData("quitTaxi", false);
		}
		else {
			// we dont need a warning if they want to quit a job that they are not having lol.
			// could be a nice easter egg, though.
			player.message(str.format("<color=yellow>Error: Cant quit a job you dont have!11!!</color><color=red> The Devs are watching you.. </color>"));
		}
	}
}

event onPlayerJoined(player) {
	playerID = player.id;
	Result = database.execute("SELECT * FROM taxiDriver WHERE steamID64 = '" + playerID + "';");

	if (Result.count != 0) {
		player.addGroup("TaxiDriver");
		player.message(str.format("<color=yellow>Welcome back! You are back on your job as TaxiDriver.</color>"));
	}
}

event onPlayerQuit(player) {
	playerID = player.id;
	Result = database.execute("SELECT * FROM taxiDriver WHERE steamID64 = '" + playerID + "';");

	if (Result.count != 0) {
		player.removeGroup("TaxiDriver"); //to avoid errors if groups persist.
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// EVERYTHING RELATED TO GETTING OR QUITTING THE JOB END
/////////////////////////////////////////////////////////////////////////////////////////