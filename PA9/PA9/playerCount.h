#include <SFML/Network.hpp>


class playerCount {

public:
	playerCount() { status = 0; }

	void minusPlayer() {
		sf::Http::Request drequest("/dPlayer", sf::Http::Request::Get);

		// send the request
		sf::Http dhttp("http://api.seanmh.net", 80);
		sf::Http::Response dresponse = dhttp.sendRequest(drequest);

		status = 0;
	}


	void addPlayer() {
		sf::Http::Request drequest("/nPlayer", sf::Http::Request::Get);
		sf::Http dhttp("http://api.seanmh.net", 80);
		sf::Http::Response dresponse = dhttp.sendRequest(drequest);
		status = 0;
	}

	std::string getPlayers() {

		std::string pCount, resp, final;
		sf::Http::Request drequest("/Players", sf::Http::Request::Get);

		// send the request
		sf::Http dhttp("http://api.seanmh.net", 80);
		sf::Http::Response dresponse = dhttp.sendRequest(drequest);
		
		if (dresponse.getStatus() == 1001)
		{
			pCount = "Not Connected";
		}
		else {
			pCount = "Players online: ";
			resp = dresponse.getBody();
			final = resp[15];
			pCount.append(final);
			return pCount;
		}

	}
private:
	int status;


};