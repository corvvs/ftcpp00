CXX			:=	clang++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 --pedantic
NAME		:=	megaphone
SRCS		:=	megaphone.cpp
OBJS		:=	$(SRCS:.cpp=.o)

.PHONY		:	all clean fclean re

all			:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(NAME)		:	all

clean		:
	$(RM) -rf $(OBJS)

fclean		:	clean
	$(RM) $(NAME)

re			:	fclean all
