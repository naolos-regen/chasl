//
// Created by nao on 11/12/25.
//

#ifndef CHASL_RUNNABLE_H
#define CHASL_RUNNABLE_H

class Runnable
{
public:
	virtual ~Runnable() = default;

private:
	virtual bool run() = 0;
	virtual bool shutdown() = 0;
};

#endif //CHASL_RUNNABLE_H
