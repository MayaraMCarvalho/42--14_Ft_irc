# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:33:22 by macarval          #+#    #+#              #
#    Updated: 2024/08/20 00:43:11 by lucperei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv
TEST_NAME	= test_runner

SRCS		= main.cpp IrcServer.cpp MsgHandler.cpp \
			\
			Channel.cpp ChannelList.cpp \
			\
			Client.cpp ClientList.cpp \
			\
			Command.cpp commandInvite.cpp commandJoin.cpp commandKick.cpp \
			commandMode.cpp commandPart.cpp commandPrivmsg.cpp commandQuit.cpp \
			commandSetup.cpp \
			\
			errorsCode.cpp infos.cpp utils.cpp utilsMode.cpp \
			validations.cpp verify.cpp \
			\
			Logger.cpp ConsoleLogger.cpp FileLogger.cpp NullLogger.cpp

TESTS_SRCS  = src/tests/UnitTests/IRCServerTest.cpp src/tests/UnitTests/ClientTest/ClientTest.cpp \
			src/tests/UnitTests/ClientTest/ClientListTest.cpp src/tests/UnitTests/mainTest.cpp \
			src/tests/UnitTests/MsgHandlerTest.cpp \
			src/tests/UnitTests/ChannelTest/ChannelTest.cpp \
			src/tests/UnitTests/ChannelTest/ChannelListTest.cpp \
			src/tests/UnitTests/Bonus/BotTest.cpp \
			src/tests/UnitTests/Bonus/FileTransferTest.cpp \
			src/tests/UnitTests/Commands/ChannelCommandsTest.cpp \
			src/tests/UnitTests/Helpers/Helpers.cpp
# src/tests/UnitTests/CommandsTest/CommandsTest.cpp
			
INTEG_TESTS = tests/IntegrationTests/IRCServerIntegrationTest.cpp

VPATH		= src/ src/channel src/client src/commands src/logger \
			src/commands/utils tests/
OBJS_PATH	= obj
INCLUDE		= -I./include -I./include/channel \
			-I./include/client -I./include/commands \
			-I./include/logger -I./include/utils

OBJS_PATH	= obj
OBJS 		= $(addprefix $(OBJS_PATH)/, $(SRCS:.cpp=.o))
TESTS_OBJS  = $(addprefix $(OBJS_PATH)/, $(TESTS_SRCS:src/tests/UnitTests/%.cpp=src/tests/UnitTests/%.o))

FLAGS		= -g3 -Wall -Wextra -Werror -g -std=c++98 -Wpedantic
CC			= c++

# Regular colors
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
RESET		= \033[0m

# Bold
BRED		= \033[1;31m
BGREEN		= \033[1;32m
BYELLOW		= \033[1;33m
BBLUE		= \033[1;34m
BPURPLE		= \033[1;35m
BCYAN		= \033[1;36m
BWHITE		= \033[1;37m

BRANCH_FILE	= .branch_name
DEV_BRANCH	= develop
MAIN_BRANCH	= master

OBJS		= $(addprefix $(OBJS_PATH)/, $(SRCS:.cpp=.o))

all: 		$(NAME)

$(NAME): 	$(OBJS_PATH) $(OBJS)
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
			@echo "\n$(CYAN)$(NAME): $(GREEN)Done!$(RESET)\n"

$(OBJS_PATH):
			@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/src/tests/UnitTests:
	@mkdir -p $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(OBJS_PATH)/src/tests/UnitTests/ChannelTest
	@mkdir -p $(OBJS_PATH)/src/tests/UnitTests/ClientTest
	@mkdir -p $(OBJS_PATH)/src/tests/UnitTests/Commands
	@mkdir -p $(OBJS_PATH)/src/tests/UnitTests/Helpers
	@mkdir -p $(OBJS_PATH)/src/tests/UnitTests/Bonus

$(OBJS_PATH)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)$(NAME) $(YELLOW)objects..." $@
	@echo -n "\n"

$(OBJS_PATH)/src/tests/UnitTests/%.o: src/tests/UnitTests/%.cpp | $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)test objects...$(RESET)" $@
	@echo -n "\n"

$(OBJS_PATH)/src/tests/UnitTests/ChannelTest/%.o: src/tests/UnitTests/ChannelTest/%.cpp | $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)test objects...$(RESET)" $@
	@echo -n "\n"

$(OBJS_PATH)/src/tests/UnitTests/ClientTest/%.o: src/tests/UnitTests/ClientTest/%.cpp | $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)test objects...$(RESET)" $@
	@echo -n "\n"

$(OBJS_PATH)/src/tests/UnitTests/Commands/%.o: src/tests/UnitTests/Commands/%.cpp | $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)test objects...$(RESET)" $@
	@echo -n "\n"

$(OBJS_PATH)/src/tests/UnitTests/Helpers/%.o: src/tests/UnitTests/Helpers/%.cpp | $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)test objects...$(RESET)" $@
	@echo -n "\n"

$(OBJS_PATH)/src/tests/UnitTests/Bonus/%.o: src/tests/UnitTests/Bonus/%.cpp | $(OBJS_PATH)/src/tests/UnitTests
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo -n "$(YELLOW)Generating $(CYAN)test objects...$(RESET)" $@
	@echo -n "\n"

# Compile and run tests
test: $(OBJS_PATH) $(OBJS_PATH)/src/tests/UnitTests $(OBJS) $(TESTS_OBJS)
	@$(CC) $(FLAGS) $(INCLUDE) $(filter-out $(OBJS_PATH)/main.o, $(OBJS)) $(TESTS_OBJS) -o $(TEST_NAME)
	@./$(TEST_NAME)
	@rm -f $(TEST_NAME)

clean:
			@rm -rf $(OBJS_PATH)
			@echo "$(CYAN)$(NAME): $(GREEN)Clean done!$(RESET)"
			@rm -f test_runner

fclean:		clean
			@rm -f $(NAME)
			@echo "$(CYAN)$(NAME): $(GREEN)Full clean done!$(RESET)"


re:			fclean all

comp:
			clear
			@make --no-print-directory -s re
			@./$(NAME)

val:
			clear
			@make --no-print-directory -s re
			@valgrind ./$(NAME)

new-branch:
			git checkout $(DEV_BRANCH)
			git pull origin $(DEV_BRANCH)
			@echo "$(BGREEN)Enter the name of the new branch: "; \
			read branch_name; \
			feature_branch="feature/$$branch_name"; \
			echo $$feature_branch; \
			echo $$feature_branch > $(BRANCH_FILE); \
			echo "Branch $$feature_branch created."; \
			git checkout -b $$(cat $(BRANCH_FILE)); \
			git push --set-upstream origin $$(cat $(BRANCH_FILE))

git:
			clear
			@make --no-print-directory fclean
			@git add . :!*$(BRANCH_FILE)
			@git status
			@echo "$(BPURPLE)Choose the commit type:"; \
			echo "$(BYELLOW)1. feat: $(WHITE)Adds a new feature to your codebase"; \
			echo "$(BYELLOW)2. fix: $(WHITE)Solves a problem in your codebase"; \
			echo "$(BYELLOW)3. docs: $(WHITE)Documentation changes"; \
			echo "$(BYELLOW)4. style: $(WHITE)Formatting, spacing, etc."; \
			echo "$(BYELLOW)5. refactor: $(WHITE)Refactoring code used in production, e.g. renaming a variable"; \
			echo "$(BYELLOW)6. test: $(WHITE)Adding tests, refactoring tests"; \
			echo "$(BYELLOW)7. chore: $(WHITE)Adjust build script, updating dependencies, makefile etc"; \
			read type_choice; \
			case $$type_choice in \
						1) type="feat" ;; \
						2) type="fix" ;; \
						3) type="docs" ;; \
						4) type="style" ;; \
						5) type="refactor" ;; \
						6) type="test" ;; \
						7) type="chore" ;; \
						*) echo "$(BRED)Invalid choice"; exit 1 ;; \
			esac; \
			echo -n "\n"; \
			echo "$(BGREEN)Enter the commit message:"; \
			read msg; \
			echo -n "\n"; \
			echo "$(BBLUE)"; \
			git commit -m "[ft_irc] $$type: $$msg"; \
			git checkout $(DEV_BRANCH); \
			git pull origin $(DEV_BRANCH); \
			git checkout $(shell cat $(BRANCH_FILE)); \
			git merge $(DEV_BRANCH); \
			git push origin $(shell cat $(BRANCH_FILE)); \

delete-branch:
			git checkout $(DEV_BRANCH)
			git pull origin $(DEV_BRANCH)
			git checkout $(shell cat $(BRANCH_FILE))
			git merge $(DEV_BRANCH)
			git checkout $(DEV_BRANCH)
			git merge $(shell cat $(BRANCH_FILE))
			git push origin $(DEV_BRANCH)
			git branch -d $(shell cat $(BRANCH_FILE))
			git push origin --delete $(shell cat $(BRANCH_FILE))

merge-to-master:
			git checkout $(MASTER_BRANCH)
			git pull origin $(MASTER_BRANCH)
			git merge $(DEV_BRANCH)
			git push origin $(MASTER_BRANCH)

lazy:
			@clear
			@lazygit

install:
			@sudo add-apt-repository ppa:lazygit-team/release
			@sudo apt-get update
			@sudo apt-get install lazygit

.PHONY:		all re clean fclean comp val git lazy install
