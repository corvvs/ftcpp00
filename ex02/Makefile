CXX			:=	clang++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98
NAME		:=	test
SRCS		:=	test.cpp Account.cpp
OBJS		:=	$(SRCS:.cpp=.o)

.PHONY:		all clean fclean re

all:		$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(NAME):	all

clean:
	$(RM) -rf $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY		:	diff

diff:		all
	bash diff.sh

