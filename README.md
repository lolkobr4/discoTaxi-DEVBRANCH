# taxiScript
Taxi Script with chat based functions. Connected with a Database, designed for uScript for Unturned 3.

# MySQL setup containing:

	requestID	->		requestID
	requester	->		requestname
	location	->		X,Y,Z
	accepted	->		tinyint 0/1
	jobsDone	->		int

	Tables:
		taxiRequest:
			rowID
			ID			=		0		
			requestName =		1
			requestID	=		2
			requestLocation	=	3		// returns X,Y,Z
			accepted		=	4		// returns "True"/"False"

		
# Code based:
	disco (https://www.youtube.com/watch?v=G_H0rJj1gJc)
	Accept as driver
	driver <-> customer // private chat
	Basic help cmd
	discord whook
	createMarker
	end a job
	setup taxiDriver Permission / people need to "apply"
