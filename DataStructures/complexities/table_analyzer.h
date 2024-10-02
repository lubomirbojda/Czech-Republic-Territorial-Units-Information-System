#pragma once

#pragma once

#include <complexities/complexity_analyzer.h>
#include <libds/adt/table.h>
#include <random>

namespace ds::utils
{
    /**
     * @brief Common base for list analyzers.
     */
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void growToSize(Table& structure, size_t size) override;

        size_t getRandomIndex() const;
        int getRandomData() const;
        int index__ = 0;

    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngIndex_;
        size_t index_;
        int data_;
        
    };




    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    /**
     * @brief Analyzes complexity of an erasure at the beginning.
     */
    template<class Table>
    class TableFindAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };





    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer();
    };








    template<class Table>
    inline TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name),
        rngData_(144),
        rngIndex_(144),
        index_(0),
        data_(0)
    {
        this->registerBeforeOperation([this](Table& table)
            {
                std::uniform_int_distribution<size_t> indexDist(0, table.size() - 1);
                index_ = indexDist(rngIndex_);
                data_ = rngData_();
            });
    }

    template<class Table>
    inline void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {
        structure.clear();
        const size_t toInsert = size - structure.size();
        for (size_t i = 0; i < toInsert; ++i)
        {
            structure.insert(i, rngData_());
        }
    }

    template<class Table>
    inline size_t TableAnalyzer<Table>::getRandomIndex() const
    {
        return index_;
    }

    template<class Table>
    inline int TableAnalyzer<Table>::getRandomData() const
    {
        return data_;
    }




    template<class Table>
    inline TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {
    }

    template<class Table>
    inline void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
        //structure.insert(getRandomIndex(), getRandomData());
        //index__++;
    }




    template<class Table>
    inline TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {
    }

    template<class Table>
    inline void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.find(this->getRandomIndex());
    }



    inline TablesAnalyzer::TablesAnalyzer() :
        CompositeAnalyzer("Tables")
    {
        this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::HashTable<int, int>>>("hashtable-insert"));
        this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::HashTable<int, int>>>("hashtable-find"));
    }
}