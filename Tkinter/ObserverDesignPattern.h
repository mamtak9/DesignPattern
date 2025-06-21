#pragma once
#include<iostream>
#include<vector>
using namespace std;
//abstract class
class Subscriber
{
public:
	virtual void update(string noti) = 0;
};

class ConcreteSubscriber :public Subscriber {
	string name;
	string notification;
public:
	ConcreteSubscriber(string name) {
		this->name = name;
	}
	void update(string noti) override{
		notification = noti;
		cout << "Hey "<<name<<",\n"<<notification;
	}
};


class YoutubeChannel {
public:
	virtual void subscribe(Subscriber* u) = 0;
	virtual void unsubscribe(Subscriber* u) = 0;
	virtual void notify(string content) = 0;
	virtual void uploadVideos(string title,string author)=0;
	virtual ~YoutubeChannel() {};
};


class ConcreteYoutubeChannel: public YoutubeChannel {
	string channelName;
	vector<Subscriber*>subscriberList;
public:
	ConcreteYoutubeChannel(string channelName) {
		this->channelName = channelName;
		cout << channelName << "created\n";
	}
	void subscribe(Subscriber* u) override {
		subscriberList.push_back(u);
	}
	
	void unsubscribe(Subscriber* u) override {
		auto it = find(subscriberList.begin(), subscriberList.end(), u);
		if (it != subscriberList.end()) {
			subscriberList.erase(it);
		}
	}
	void notify(string content) override{
		for (auto x : subscriberList) {
			x->update(content);
		}
		return;
	
	};
	void uploadVideos(string title, string author) {
		string content = "New Video from " + channelName + " named : [" + title + "] by " + author + " released!!!\n";
		notify(content);
	}
};


int main() {
	Subscriber* A = new ConcreteSubscriber("Ama");
	Subscriber* B = new ConcreteSubscriber("Alex");
	Subscriber* C = new ConcreteSubscriber("Anna");
	Subscriber* D = new ConcreteSubscriber("Bob");
	YoutubeChannel* yt1 = new ConcreteYoutubeChannel("CodeStory ");
	YoutubeChannel* yt2 = new ConcreteYoutubeChannel("CoderArmy ");
	yt1->subscribe(A);
	yt2->subscribe(B);
	yt1->subscribe(C);
	yt1->subscribe(D);
	yt1->subscribe(B);
	yt1->uploadVideos("Trailer XXX", "Evan");
	yt1->unsubscribe(B);
	yt1->uploadVideos("GHY 99900", "King");
	yt2->uploadVideos("Jungle Book BGY", "Chris");

}



