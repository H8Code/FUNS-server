#ifndef SCHEDULESID
#define SCHEDULESID

#include "FunsResourceImpl.h"

class SchedulesIDImpl
: public FunsResourceImpl {
public:

	void get_handler(const shared_ptr<Session> &session)
	{
		const auto id = session->get_request()->get_path_parameter("id", true);
		auto data = db->get_schedule_by_id(id);
		session->close(OK, data);
	}
};

#endif // SCHEDULESID

