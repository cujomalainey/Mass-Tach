using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Server.Database;

namespace Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ReportsController : ControllerBase
    {

        ServerContext _serverContext;
        public ReportsController(ServerContext serverContext)
        {
            _serverContext = serverContext;
        }

    }
}