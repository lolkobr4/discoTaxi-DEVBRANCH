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

event onPlayerQuit(player) {
	if (taxicall.contains(player.id)) { taxicall.remove(player.id); }
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

command orderTaxi() {
	//permission = "taxi.call";
	execute() {

		location = player.position;
		namePlayer = player.name;

		foreach(taxiDriver in server.players) {
			//if (taxi.hasPermission("taxiDriver")) { taxi.message(player.name + " has called a taxi. Destination: " + reason + ". Accept this job? /accept"); }
			if (true) { //change that to permissions once created.
				taxiDriver.message(str.format("<color=yellow>{0} has ordered a Taxi. Use /accept to accept the order.</color>", player.name));
			}
		}

		taxicall.add(player.id);
		player.message("You have already called a taxi!");
		wait.seconds(60, waitRemove(player.id));
		}
	}
}