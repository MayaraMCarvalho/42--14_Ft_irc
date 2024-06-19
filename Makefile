# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:33:22 by macarval          #+#    #+#              #
#    Updated: 2024/06/18 09:06:05 by macarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		= main.cpp Bot.cpp Channel.cpp ChannelList.cpp Client.cpp \
			ClientList.cpp Commands.cpp FileTransfer.cpp IrcServer.cpp

VPATH		= src/
OBJS_PATH	= obj
INCLUDE		= -I./include

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

BRANCH_FILE = .branch_name
DEVELOP_BRANCH = develop
MAIN_BRANCH = master

OBJS 		= $(addprefix $(OBJS_PATH)/, $(SRCS:.cpp=.o))

all: 		$(NAME)

$(NAME): 	$(OBJS_PATH) $(OBJS)
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
			@echo "\n$(CYAN)$(NAME): $(GREEN)Done!$(RESET)\n"

$(OBJS_PATH):
			@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: %.cpp
			@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
			@echo -n "$(YELLOW)Generating $(CYAN)$(NAME) $(YELLOW)objects..." $@
			@echo -n "\n"

clean:
			@rm -rf $(OBJS_PATH)
			@echo "$(CYAN)$(NAME): $(GREEN)Clean done!$(RESET)"

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
			git checkout $(DEVELOP_BRANCH)
			git pull origin $(DEVELOP_BRANCH)
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
			git checkout $(DEVELOP_BRANCH); \
			git pull origin $(DEVELOP_BRANCH); \
			git checkout $(shell cat $(BRANCH_FILE)); \
			git merge $(DEVELOP_BRANCH); \
			git push origin $(shell cat $(BRANCH_FILE)); \

delete-branch:
			git checkout $(DEVELOP_BRANCH)
			git pull origin $(DEVELOP_BRANCH)
			git checkout $(shell cat $(BRANCH_FILE))
			git merge $(DEVELOP_BRANCH)
			git checkout $(DEVELOP_BRANCH)
			git merge $(shell cat $(BRANCH_FILE))
			git push origin $(DEVELOP_BRANCH)
			git branch -d $(shell cat $(BRANCH_FILE))
			git push origin --delete $(shell cat $(BRANCH_FILE))

merge-to-master:
			git checkout $(MASTER_BRANCH)
			git pull origin $(MASTER_BRANCH)
			git merge $(DEVELOP_BRANCH)
			git push origin $(MASTER_BRANCH)

lazy:
			@clear
			@lazygit

install:
			@sudo add-apt-repository ppa:lazygit-team/release
			@sudo apt-get update
			@sudo apt-get install lazygit

.PHONY:		all re clean fclean comp val git lazy install
