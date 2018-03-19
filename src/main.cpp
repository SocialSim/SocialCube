#include "AgentBuilder/AgentBuilder.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp"

int main() {

    AgentBuilder<SimpleGithubUserAgent, SimpleGithubObjectAgent> builder;
    builder.build();
}
