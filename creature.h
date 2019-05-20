#pragma once

class Creature
{
    public:
        virtual bool isSurviving(int neighbours) const = 0;   // Abstract class
        virtual std::string symbol() const = 0;

        virtual Creature* prototype() const = 0;
};

class Basic : public Creature
{
    public:
        virtual bool isSurviving(int neighbours) const override;
        virtual std::string symbol() const override;
        Creature* prototype() const override;
        static Creature* proto;

};

class Friendly : public Creature
{
    public:
        virtual bool isSurviving(int neighbours) const override;
        virtual std::string symbol() const override;
        Creature* prototype() const override;
        static Creature* proto;
};

class Unfriendly : public Creature
{
    public:
        virtual bool isSurviving(int neighbours) const override;
        virtual std::string symbol() const override;
        Creature* prototype() const override;
        static Creature* proto;
};


class CreatureFactory
{
    public:

        // I used a string instead of ENUM as a shortcut in this exercise
        // enum type{
        //     BASIC,
        //     FRIENDLY,
        //     UNFRIENDLY
        // };

        CreatureFactory() = default;
        ~CreatureFactory() = default;
        static Creature* make(std::string type = "b");
};