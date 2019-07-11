using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace Server.Database
{
    public class ServerContext : DbContext
    {
        public ServerContext(DbContextOptions<ServerContext> options) : base(options)
        {

        }
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
        }
        
    }
}