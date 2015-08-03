#ifndef INFORMATIONMESSAGEHANDLER_H
#define INFORMATIONMESSAGEHANDLER_H

#include <OpenBattleCore.h>
#include <Generated.h>
using namespace OpenBattle;

#include "logger.h"

class InformationMessageHandler : public MessageHandler {
	Logger *logger;
public:
	InformationMessageHandler(Logger *logger) : logger(logger) { }
	unsigned char type() { return MSG_INFORMATION; }
	void invoke(Message *msg) { this->logger->write(((InformationMessage*)msg)->message); }
};

#endif // INFORMATIONMESSAGEHANDLER_H

